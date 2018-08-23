/**
*   @file MomentField.h
*   @brief Stores information about the trial moment field pattern.
*   @author Ross Knapman
*   @date 21/08/2018
*/


#ifndef INC_3DDIPOLEFIELD_MOMENTFIELD_H
#define INC_3DDIPOLEFIELD_MOMENTFIELD_H

#include <vector>
#include <complex>
#include <string>
#include <pybind11/numpy.h>

namespace py = pybind11;


class MomentField
{
private:
    py::array_t<double> propagationVector;
    double propagationWavelength;  // The wavelength of each propagation vector, in unit cells
    py::array_t<double> fourierComponent;
    int type;  // 1 = ferromagnet; 2 = antiferromagnet; 3 = single-k helical state; 4 = triple-k "skyrmion" state (etc. if more states are added)

public:

    // Constructors for various structures
    MomentField(py::array_t<double> fourierComponent);  // For ferromagnetic
    MomentField(py::array_t<double> propagationVector, double propagationWavelength, py::array_t<double> fourierComponent);  // For antiferromagnetic
    MomentField(double propagationWavelength, std::string type);  // For single-k(type = "singleK") or triple-k states (type = "tripleK")

    // Setters
    void setPropagationVector(py::array_t<double> propagationVectorIn) { propagationVector = propagationVectorIn; }
    void setPropagationWavelength(double propagationWavelengthIn) { propagationWavelength = propagationWavelengthIn; }
    void setFourierComponent(py::array_t<double> fourierComponentIn) { fourierComponent = fourierComponentIn; }
    void setType(int typeIn) { type = typeIn; }

    // Getters
    py::array_t<double> getPropagationVector() { return propagationVector; }
    double getPropagationWavelength() { return propagationWavelength; }
    py::array_t<double> getFourierComponent() { return fourierComponent; }
    std::string getType();

    // Misc.
    std::vector<double> getMoment(double x, double y, double z);  // x, y, z in unit cells

};


#endif //INC_3DDIPOLEFIELD_MOMENTFIELD_H
