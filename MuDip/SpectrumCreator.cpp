//
// Created by Ross Knapman on 12/08/2018.
//

#include "SpectrumCreator.h"

#include <iostream>
#include <cmath>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

SpectrumCreator::SpectrumCreator(MomentField momentFieldIn, Sample sampleIn, py::array_t<double> muonPositionsIn,
                                 int startCellIn, int endCellIn, int resolutionIn, int radiusIn, py::array_t<double> BAppliedIn, std::string outputPathIn) :

// Initialiser list
momentField(momentFieldIn), sample(sampleIn), muonPositions(muonPositionsIn), startCell(startCellIn), endCell(endCellIn),
resolution(resolutionIn), radius(radiusIn), BApplied(BAppliedIn), outputPath(outputPathIn) {}


py::array_t<double> SpectrumCreator::outputSpectrum()
{
    int componentLength = pow(((endCell - startCell) / resolution), 3) * muonPositions.size();
    py::array_t<double> Bmags(componentLength);
    int Bindex = 0;

#pragma omp parallel for collapse(3)  // Parallelise the for loop
    for (int i = startCell; i < endCell; i = i + resolution)
    {
        for (int j = startCell; j < endCell; j = j + resolution)
        {
            for (int k = startCell; k < endCell; k = k + resolution)
            {
                std::cout << i << " " << j << " " << k << std::endl;
                for (int muonIndex = 0; muonIndex < muonPositions.size(); muonIndex++)
                {
                    double x = i + muonPositions.mutable_at(muonIndex, 0);
                    double y = j + muonPositions.mutable_at(muonIndex, 1);
                    double z = k + muonPositions.mutable_at(muonIndex, 2);
                    std::vector<double> B = sample.getTotalField(x, y, z, radius);
                    B[0] = B[0] + BApplied.mutable_at(0);  // Add applied magnetic field
                    B[1] = B[1] + BApplied.mutable_at(1);
                    B[2] = B[2] + BApplied.mutable_at(2);

                    std::vector<double> nVector(3);  // The unit vector along which the component of n is taken

                    // Components are random values between 0 and 1
//                    nVector[0] = (double) 2 * rand() / RAND_MAX;
//                    nVector[1] = (double) 2 * rand() / RAND_MAX;
//                    nVector[2] = (double) 2 * rand() / RAND_MAX;

                    nVector[0] = 1;
                    nVector[1] = 1;
                    nVector[2] = 1;

                    double Bcomponent = 0;
                    double magnitude = 0;

                    // Get magnitude for normalisation
                    for (int nIndex = 0; nIndex < nVector.size(); nIndex++)
                    {
                        magnitude = magnitude + pow(nVector[nIndex], 2);
                    }
                    magnitude = sqrt(magnitude);

                    // Divide by magnitude and take dot product (i.e. Bcomponent)
                    for (int nIndex = 0; nIndex < nVector.size(); nIndex++)
                    {
                        nVector[nIndex] = nVector[nIndex] / magnitude;
                        Bcomponent = Bcomponent + nVector[nIndex] * B[nIndex];
                    }

                    Bmags.mutable_at(Bindex) = Bcomponent;
                    Bindex++;
                }
            }
        }
    }
    return Bmags;
}
