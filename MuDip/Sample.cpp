#include "Sample.h"
#include <iostream>
#include "LorentzSphere.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;



Sample::Sample(double aIn, MomentField momentFieldIn) : momentField(momentFieldIn)
{
    setA(aIn);
    setMomentField(momentFieldIn);
}


/**
*   Get the field as a result of dipoles wihtin a Lorentz sphere at an arbitrary point.
*   @param x The x-position of the point at which the dipole field is to be evaluated.
*   @param y The y-position of the point at which the dipole field is to be evaluated.
*   @param z The z-position of the point at which the dipole field is to be evaluated.
*   @param radius The radius of the Lorentz sphere.
*   @return The dipolar field as a vector.
*/
py::array_t<double> Sample::getDipoleField(double x, double y, double z, double radius)
{
    LorentzSphere *lorentzSphere = new LorentzSphere(x, y, z, *this, radius);
    std::vector<double> dipoleField = lorentzSphere->calculateDipoleField();

    // Convert output dipole field to numpy array
    py::array_t<double> outputDipoleField(dipoleField.size());

    for (int i = 0; i < dipoleField.size(); i++)
    {
        outputDipoleField.mutable_at(i) = dipoleField[i];
    }

    return outputDipoleField;
}


/**
*   Get the Lorentz field for a Lorentz sphere of a given radius at an arbitrary point.
*   @param x The x-position of the point at which the dipole field is to be evaluated.
*   @param y The y-position of the point at which the dipole field is to be evaluated.
*   @param z The z-position of the point at which the dipole field is to be evaluated.
*   @param radius The radius of the Lorentz sphere.
*   @return The Lorentz field as a vector.
*/
py::array_t<double> Sample::getLorentzField(double x, double y, double z, double radius)
{
    LorentzSphere *lorentzSphere = new LorentzSphere(x, y, z, *this, radius);
    std::vector<double> lorentzField = lorentzSphere->calculateLorentzField();

    // Convert the Lorentz field to numpy array
    py::array_t<double> outputLorentzField(lorentzField.size());

    for (int i = 0; i < lorentzField.size(); i++)
    {
        outputLorentzField.mutable_at(i) = lorentzField[i];
    }

    return outputLorentzField;
}


/**
*   Get the total field (dipolar + Lorentz) at a given point.
*   @param x The x-position of the point at which the dipole field is to be evaluated.
*   @param y The y-position of the point at which the dipole field is to be evaluated.
*   @param z The z-position of the point at which the dipole field is to be evaluated.
*   @param radius The radius of teh Lorentz sphere.
*   @return The total field as a vector.
*/
py::array_t<double> Sample::getTotalField(double x, double y, double z, double radius)
{
    py::array_t<double> dipoleField = getDipoleField(x, y, z, radius);
    py::array_t<double> lorentzField = getLorentzField(x, y, z, radius);

    py::array_t<double> totalField(dipoleField.size());

    // Vector addition of dipole and Lorentz fields
    for (int i = 0; i < len(totalField); i++)
    {
        totalField.mutable_at(i) = dipoleField.mutable_at(i) + lorentzField.mutable_at(i);
    }

    return totalField;
}
