/**
*   @file SpectrumCreator.h
*   @brief Object which contains the functions to output a list of the magnetic
*   field components sampled around the crystal to create a spectrum.
*   @author Ross Knapman
*   @date 21/08/2018
*/


#ifndef INC_3DDIPOLEFIELD_SPECTRUMCREATOR_H
#define INC_3DDIPOLEFIELD_SPECTRUMCREATOR_H

#include "LorentzSphere.h"
#include <pybind11/pybind11.h>
#include<pybind11/numpy.h>

namespace py = pybind11;


class SpectrumCreator
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

public:
    SpectrumCreator(MomentField momentFieldIn, Sample sampleIn, py::array_t<double> muonPositionsIn,
                    int startCellIn, int endCellIn, int resolutionIn, int radiusIn, py::array_t<double> BAppliedIn);

    // Setters (we use an initialiser list in the constructor, hence these would only be called by the user)
    void setMomentField(MomentField momentFieldIn) { momentField = momentFieldIn; }
    void setSample(Sample sampleIn) { sample = sampleIn; }
    void setMuonPositions(py::array_t<double> muonPositionsIn) { muonPositions = muonPositionsIn; }
    void setStartCell(int startCellIn) { startCell = startCellIn; }
    void setEndCell(int endCellIn) { endCell = endCellIn; }
    void setResolution(int resolutionIn) { resolution = resolutionIn; }
    void setRadius(int radiusIn) { radius = radiusIn; }
    void setBApplied(py::array_t<double> BAppliedIn) { BApplied = BAppliedIn; }

    // Getters
    MomentField getMomentField() { return momentField; }
    Sample getSample() { return sample; }
    py::array_t<double> getMuonPositions() { return muonPositions; }
    int getStartCell() { return startCell; }
    int getEndCell() { return endCell; }
    int getResolution() { return resolution; }
    int getRadius() { return radius; }
    py::array_t<double> getBApplied() { return BApplied; }

    // What the user is actually supposed to call
    py::array_t<double> outputSpectrum();

};


#endif //INC_3DDIPOLEFIELD_SPECTRUMCREATOR_H
