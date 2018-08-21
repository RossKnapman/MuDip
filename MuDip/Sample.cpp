#include "Sample.h"
#include <iostream>
#include "LorentzSphere.h"


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
std::vector<double> Sample::getDipoleField(double x, double y, double z, double radius)
{
    LorentzSphere *lorentzSphere = new LorentzSphere(x, y, z, *this, radius);
    return lorentzSphere->calculateDipoleField();
}


/**
*   Get the Lorentz field for a Lorentz sphere of a given radius at an arbitrary point.
*   @param x The x-position of the point at which the dipole field is to be evaluated.
*   @param y The y-position of the point at which the dipole field is to be evaluated.
*   @param z The z-position of the point at which the dipole field is to be evaluated.
*   @param radius The radius of the Lorentz sphere.
*   @return The Lorentz field as a vector.
*/
std::vector<double> Sample::getLorentzField(double x, double y, double z, double radius)
{
    LorentzSphere *lorentzSphere = new LorentzSphere(x, y, z, *this, radius);
    return lorentzSphere->calculateLorentzField();
}


/**
*   Get the total field (dipolar + Lorentz) at a given point.
*   @param x The x-position of the point at which the dipole field is to be evaluated.
*   @param y The y-position of the point at which the dipole field is to be evaluated.
*   @param z The z-position of the point at which the dipole field is to be evaluated.
*   @param radius The radius of teh Lorentz sphere.
*   @return The total field as a vector.
*/
std::vector<double> Sample::getTotalField(double x, double y, double z, double radius)
{
    std::vector<double> dipoleField = getDipoleField(x, y, z, radius);
    std::vector<double> lorentzField = getLorentzField(x, y, z, radius);

    std::vector<double> totalField(dipoleField.size());

    // Vector addition of dipole and Lorentz fields
    for (int i = 0; i < totalField.size(); i++)
    {
        totalField[i] = dipoleField[i] + lorentzField[i];
    }
    return totalField;
}
