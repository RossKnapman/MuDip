#include "SpectrumCreator.h"
#include <iostream>
#include <cmath>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;


SpectrumCreator::SpectrumCreator(MomentField momentFieldIn, Sample sampleIn, py::array_t<double> muonPositionsIn,
                                 int startCellIn, int endCellIn, int resolutionIn, int radiusIn, py::array_t<double> BAppliedIn) :

// Initialiser list
momentField(momentFieldIn), sample(sampleIn), muonPositions(muonPositionsIn), startCell(startCellIn), endCell(endCellIn),
resolution(resolutionIn), radius(radiusIn), BApplied(BAppliedIn) {}


/**
*   Obtain a 1d array of magnetic field components sampled throughout the crystal,
*   which can be used to generate a spectrum.
*   @return 1d array of magnetic field components sampled through the crystal.
*/
py::array_t<double> SpectrumCreator::outputSpectrum()
{
    int componentLength = pow(((endCell - startCell) / resolution), 3) * len(muonPositions);
    py::array_t<double> Bmags(componentLength);
    int Bindex = 0;

#pragma omp parallel for collapse(3)  // Parallelise the for loop
    for (int i = startCell; i < endCell; i = i + resolution)
    {
        for (int j = startCell; j < endCell; j = j + resolution)
        {
            for (int k = startCell; k < endCell; k = k + resolution)
            {
                for (int muonIndex = 0; muonIndex < len(muonPositions); muonIndex++)
                {
                    py::print(i, j, k);
                    double x = i + muonPositions.mutable_at(muonIndex, 0);
                    double y = j + muonPositions.mutable_at(muonIndex, 1);
                    double z = k + muonPositions.mutable_at(muonIndex, 2);

                    py::array_t<double> B = sample.getTotalField(x, y, z, radius);

                    B.mutable_at(0) = B.mutable_at(0) + BApplied.mutable_at(0);  // Add applied magnetic field
                    B.mutable_at(1) = B.mutable_at(1) + BApplied.mutable_at(1);
                    B.mutable_at(2) = B.mutable_at(2) + BApplied.mutable_at(2);


                    std::vector<double> nVector(3);  // The unit vector along which the component of n is taken

                   //  // Get a random orientation in the positive octant
                   // nVector[0] = (double) rand() / RAND_MAX;
                   // nVector[1] = (double) rand() / RAND_MAX;
                   // nVector[2] = (double) rand() / RAND_MAX;

                    // For now, we just take the component along the arbitrary (1, 1, 1) direction
                    nVector[0] = 1;
                    nVector[1] = 1;
                    nVector[2] = 1;

                    double Bcomponent = 0;  // The component of B to be added to the output spectrum

                    // Get the magnitude of nVector
                    double magnitude = 0;

                    for (int nIndex = 0; nIndex < nVector.size(); nIndex++)
                    {
                        magnitude = magnitude + pow(nVector[nIndex], 2);
                    }
                    magnitude = sqrt(magnitude);

                    // Make nVector a unit vector and take the component of the B-field along it
                    for (int nIndex = 0; nIndex < nVector.size(); nIndex++)
                    {
                        nVector[nIndex] = nVector[nIndex] / magnitude;
                        Bcomponent = Bcomponent + nVector[nIndex] * B.mutable_at(nIndex);
                    }

                    Bmags.mutable_at(Bindex) = Bcomponent;
                    Bindex++;
                }
            }
        }
    }

    return Bmags;
}
