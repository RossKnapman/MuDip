//
// Created by Ross Knapman on 02/08/2018.
//

#include "Sample.h"

#include <iostream>

#include "LorentzSphere.h"


Sample::Sample(double aIn, MomentField momentFieldIn) : momentField(momentFieldIn)
{
    setA(aIn);
    setMomentField(momentFieldIn);
}


std::vector<double> Sample::getDipoleField(double x, double y, double z, double radius)
{
    LorentzSphere *lorentzSphere = new LorentzSphere(x, y, z, *this, radius);
    return lorentzSphere->calculateDipoleField();
}


std::vector<double> Sample::getLorentzField(double x, double y, double z, double radius)
{
    LorentzSphere *lorentzSphere = new LorentzSphere(x, y, z, *this, radius);
    return lorentzSphere->calculateLorentzField();
}


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