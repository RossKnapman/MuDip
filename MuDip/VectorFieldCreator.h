/**
*   @file VectorFieldCreator.h
*   @brief Contains the functions to output the necessary information to plot
*   a 2D slice of the magnetic and moment fields within the crystal.
*   @author Ross Knapman
*   @date 21/08/2018
*/


#ifndef INC_3DDIPOLEFIELD_VECTORFIELDCREATOR_H
#define INC_3DDIPOLEFIELD_VECTORFIELDCREATOR_H

#include "LorentzSphere.h"
#include <string>
#include <pybind11/numpy.h>

namespace py = pybind11;


class VectorFieldCreator
{
private:
    MomentField momentField;
    Sample sample;
    py::array_t<double> muonPositions;
    int startCell;
    int endCell;
    int resolution;
    int radius;
    py::array_t<double> BApplied;
    double z;

public:
    VectorFieldCreator(MomentField momentFieldIn, Sample sampleIn, py::array_t<double> muonPositionsIn,
                       int startCellIn, int endCellIn, int resolutionIn, int radius, py::array_t<double> BAppliedIn, double zIn);

    // Setters (we use an initialiser list in the constructor, hence these would only be called by the user)
    void setMomentField(MomentField momentFieldIn) { momentField = momentFieldIn; }
    void setSample(Sample sampleIn) { sample = sampleIn; }
    void setMuonPos(py::array_t<double> muonPositionsIn) { muonPositions = muonPositionsIn; }
    void setStartCell(int startCellIn) { startCell = startCellIn; }
    void setEndCell(int endCellIn) { endCell = endCellIn; }
    void setResolution(int resolutionIn) { resolution = resolutionIn; }
    void setRadius(int radiusIn) { radius = radiusIn; }
    void setBApplied(py::array_t<double> BAppliedIn) { BApplied = BAppliedIn; }
    void setZ(double zIn) { z = zIn; }

    // Getters
    MomentField getMomentField() { return momentField; }
    Sample getSample() { return sample; }
    py::array_t<double> getMuonPositions() { return muonPositions; }
    int getStartCell() { return startCell; }
    int getEndCell() { return endCell; }
    int getResolution() { return resolution; }
    int getRadius() { return radius; }
    py::array_t<double> getBApplied() { return BApplied; }
    double getZ() { return z; }

    // What the user is actually supposed to call
    py::array_t<double> outputBField();  // Output 2D magnetic field in z plane
    py::array_t<double> outputMField();  // Outut moment field in z plane

};


#endif //INC_3DDIPOLEFIELD_VECTORFIELDCREATOR_H
