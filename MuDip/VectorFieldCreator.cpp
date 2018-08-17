//
// Created by Ross Knapman on 10/08/2018.
//

#include "VectorFieldCreator.h"
#include <iostream>
#include "Crystals/Cu2OSeO3.h"


VectorFieldCreator::VectorFieldCreator(MomentField momentFieldIn, Sample sampleIn, std::vector<std::vector<double> > muonPositionsIn,
int startCellIn, int endCellIn, int resolutionIn, int radiusIn, std::vector<double> BAppliedIn, double zIn, std::string BPathIn, std::string MPathIn) :

// Initialiser list
momentField(momentFieldIn), sample(sampleIn), muonPositions(muonPositionsIn), startCell(startCellIn),
endCell(endCellIn), resolution(resolutionIn), radius(radiusIn), BApplied(BAppliedIn), z(zIn), BPath(BPathIn), MPath(MPathIn) {}


py::array_t<py::array_t<double> > VectorFieldCreator::outputBField()
{
    // Initialise the output array, which looks like [[x1, x2, ...], [y1, y1, ...], [B_x1, B_x2, ...], [B_y1, B_y2, ...]]
    py::array_t<py::array_t<double> > outputBArray(4, py::array_t<double>(pow(((endCell - startCell) / resolution), 3) * muonPositions.size()));
    double Bindex = 0;

    for (double j = startCell; j < endCell; j = j + resolution)
    {
        for (double i = startCell; i < endCell; i = i + resolution)
        {
            for (int muonIndex = 0; muonIndex < muonPositions.size(); muonIndex++)
            {
                double xPos = i + muonPositions[muonIndex][0];
                double yPos = j + muonPositions[muonIndex][1];
                double zPos = z + muonPositions[muonIndex][2];
                std::vector<double> Bfield = sample.getTotalField(xPos, yPos, zPos, radius);
                outputBArray.mutable_at(0).mutable_at(Bindex) = xPos;
                outputBArray.mutable_at(1).mutable_at(Bindex) = yPos;
                outputBArray.mutable_at(2).mutable_at(Bindex) = Bfield[0] + Bapplied[0];
                outputBArray.mutable_at(3).mutable_at(Bindex) = Bfield[1] + Bapplied[1];
                Bindex++;
            }
        }
        return outputBArray;
    }
}


py::array_t<py::array_t<double> > VectorFieldCreator::outputMField()
{
    // Initialise the output array, which looks like [[x1, x2, ...], [y1, y1, ...], [m_x1, m_x2, ...], [m_y1, m_y2, ...]]
    py::array_t<py::array_t<double> > outputMArray(4, py::array_t<double>(pow(((endCell - startCell) / resolution), 3) * muonPositions.size()));
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
                outputMArray.mutable_at(0).mutable_at(Mindex) = atomXPos;
                outputMArray.mutable_at(1).mutable_at(Mindex) = atomYPos;
                outputMArray.mutable_at(2).mutable_at(Mindex) = momentVec[0];
                outputMArray.mutable_at(3).mutable_at(Mindex) = momentVec[1];
                Mindex++;
            }
        }
    }
    return outputMArray;
}
