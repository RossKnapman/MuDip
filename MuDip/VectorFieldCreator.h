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

    // // Setters
    // void setMomentField(MomentField momentFieldIn) { momentField = momentFieldIn; }
    // void setSample(Sample sampleIn) { sample = sampleIn; }
    // void setMuonPos(py::array_t<double> muonPositionsIn) { muonPositions = muonPositionsIn; }
    // void setStartCell(int startCellIn) { startCell = startCellIn; }
    // void setEndCell(int endCellIn) { endCell = endCellIn; }
    // void setResolution(int resolutionIn) { resolution = resolutionIn; }
    // void setRadius(int radiusIn) { radius = radiusIn; }
    // void setBApplied(py::array_t<double> BAppliedIn) { BApplied = BAppliedIn; }
    // void setZ(double zIn) { z = zIn; }
    // void setBPath(std::string BPathIn) { BPath = BPathIn; }
    // void setMPath(std::string MPathIn) { MPath = MPathIn; }

    // Do I really need getters (or even setters, for that matter)?

    py::array_t<double> outputBField();  // Output 2D magnetic field in z plane
    py::array_t<double> outputMField();  // Outut moment field in z plane

};


#endif //INC_3DDIPOLEFIELD_VECTORFIELDCREATOR_H
