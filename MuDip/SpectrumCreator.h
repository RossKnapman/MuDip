//
// Created by Ross Knapman on 12/08/2018.
//

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

    py::array_t<double> outputSpectrum();

};


#endif //INC_3DDIPOLEFIELD_SPECTRUMCREATOR_H
