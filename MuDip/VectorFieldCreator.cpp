#include "VectorFieldCreator.h"
#include <iostream>
#include "Crystals/Cu2OSeO3.h"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;


VectorFieldCreator::VectorFieldCreator(MomentField momentFieldIn, Sample sampleIn, py::array_t<double> muonPositionsIn,
int startCellIn, int endCellIn, int resolutionIn, int radiusIn, py::array_t<double> BAppliedIn, double zIn) :

// Initialiser list
momentField(momentFieldIn), sample(sampleIn), muonPositions(muonPositionsIn), startCell(startCellIn),
endCell(endCellIn), resolution(resolutionIn), radius(radiusIn), BApplied(BAppliedIn), z(zIn) {}


py::array_t<double> VectorFieldCreator::outputBField()
{
    // Initialise the output array, which looks like [[x1, x2, ...], [y1, y1, ...], [B_x1, B_x2, ...], [B_y1, B_y2, ...]]
    int componentLength = pow(((endCell - startCell) / resolution), 2) * len(muonPositions);
    py::array_t<double> outputBArray({4, componentLength});
    double Bindex = 0;

    for (double j = startCell; j < endCell; j = j + resolution)
    {
        for (double i = startCell; i < endCell; i = i + resolution)
        {
            for (int muonIndex = 0; muonIndex < len(muonPositions); muonIndex++)
            {
                py::print(i, j, muonIndex);
                double xPos = i + muonPositions.mutable_at(muonIndex, 0);
                double yPos = j + muonPositions.mutable_at(muonIndex, 1);
                double zPos = z + muonPositions.mutable_at(muonIndex, 2);
                std::vector<double> Bfield = sample.getTotalField(xPos, yPos, zPos, radius);
                outputBArray.mutable_at(0, Bindex) = xPos;
                outputBArray.mutable_at(1, Bindex) = yPos;
                outputBArray.mutable_at(2, Bindex) = Bfield[0] + BApplied.mutable_at(0);
                outputBArray.mutable_at(3, Bindex) = Bfield[1] + BApplied.mutable_at(1);
                Bindex++;
            }
        }
    }
    return outputBArray;
}


py::array_t<double> VectorFieldCreator::outputMField()
{
    // Initialise the output array, which looks like [[x1, x2, ...], [y1, y1, ...], [m_x1, m_x2, ...], [m_y1, m_y2, ...]]
    int componentLength = pow(((endCell - startCell) / resolution), 2) * sample.getAtoms().size();
    py::array_t<double> outputMArray({4, componentLength});
    double Mindex = 0;

    for (double j = startCell; j < endCell; j = j + resolution)
    {
        for (double i = startCell; i < endCell; i = i + resolution)
        {
            for (int atomIndex = 0; atomIndex < sample.getAtoms().size(); atomIndex++)
            {

                double atomXPos = i + sample.getAtoms()[atomIndex].getX();
                double atomYPos = j + sample.getAtoms()[atomIndex].getY();
                double atomZPos = z + sample.getAtoms()[atomIndex].getZ();


                std::vector<double> momentVec = momentField.getMoment(atomXPos, atomYPos, z);

                if (sample.getAtoms()[atomIndex].getFlipped())
                {
                    for (int cartesianIndex = 0; cartesianIndex < momentVec.size(); cartesianIndex++)
                    {
                        momentVec[cartesianIndex] = -momentVec[cartesianIndex];
                    }
                }
                outputMArray.mutable_at(0, Mindex) = atomXPos;
                outputMArray.mutable_at(1, Mindex) = atomYPos;
                outputMArray.mutable_at(2, Mindex) = momentVec[0];
                outputMArray.mutable_at(3, Mindex) = momentVec[1];
                Mindex++;
            }
        }
    }
    
    return outputMArray;
}
