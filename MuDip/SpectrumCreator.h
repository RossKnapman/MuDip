//
// Created by Ross Knapman on 12/08/2018.
//

#ifndef INC_3DDIPOLEFIELD_SPECTRUMCREATOR_H
#define INC_3DDIPOLEFIELD_SPECTRUMCREATOR_H

#include "LorentzSphere.h"
#include<pybind11/numpy.h>

namespace py = pybind11;


class SpectrumCreator
{

private:
    MomentField momentField;
    Sample sample;
    std::vector<std::vector<double> > muonPositions;
    int startCell;
    int endCell;
    int resolution;
    int radius;
    std::vector<double> BApplied;
    std::string outputPath;

public:
    SpectrumCreator(MomentField momentFieldIn, Sample sampleIn, std::vector<std::vector<double> > muonPositionsIn,
                    int startCellIn, int endCellIn, int resolutionIn, int radiusIn, std::vector<double> BAppliedIn, std::string outputPathIn);

    py::array_t<double> outputSpectrum();

};


#endif //INC_3DDIPOLEFIELD_SPECTRUMCREATOR_H
