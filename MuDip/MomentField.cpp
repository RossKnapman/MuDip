//
// Created by Ross Knapman on 30/07/2018.
//

#include "MomentField.h"

#include <iostream>
#include <cmath>
#include <complex>
#include <cassert>


// The ferromagnetic state constructor (only takes in the Fourier component)
MomentField::MomentField(py::array_t<double> fourierComponent){
    setFourierComponent(fourierComponent);
    setType(1);
}


// The antiferromagentic state constructor
MomentField::MomentField(py::array_t<double> propagationVector, double propagationWavelength,
                         py::array_t<double> fourierComponent)
{
    setPropagationVector(propagationVector);
    setPropagationWavelength(propagationWavelength);
    setFourierComponent(fourierComponent);
    setType(2);

    assert(propagationWavelength != 0);  // This would be the ferromagnetic state

    // Get the magnitude of the vector
    double magnitude = 0;
    for (int i = 0; i < propagationVector.size(); i++)
    {
        magnitude = magnitude + pow(propagationVector[i], 2);
    }

    magnitude = sqrt(magnitude);

    for (int i = 0; i < propagationVector.size(); i++)
    {
        propagationVector.mutable_at(i) = propagationVector.mutable_at(i) / magnitude;

        // Account for wavelength
        propagationVector.mutable_at(i) = propagationVector.mutable_at(i) * 2 * M_PI / propagationWavelength;
    }
}


// The constructor for the single- and triple-k states described in Tom's paper
MomentField::MomentField(double propagationWavelength, std::string type)
{
    setPropagationWavelength(propagationWavelength);

    if (type == "singleK")
    {
        setType(3);
    }
    else if (type == "tripleK")  // Skyrmion state
    {
        setType(4);
    }
}


// Getter for type
std::string MomentField::getType()
{
    switch(type)
    {
        case 1 :
            return "Ferromagnet";
            break;

        case 2 :
            return "Antiferromagnet";
            break;

        case 3 :
            return "Single-k helical state";
            break;

        case 4:
            return "Triple-k 'skyrmion' state";
            break;
    }
}


std::vector<double> MomentField::getMoment(double x, double y, double z)
{

    std::vector<double> returnMoment(3);

    switch(type)
    {

        case 0 :
        {
            std::cout << "No type set!";
        }

        case 1 :
        {
            // Ferromagnet
            for (int i = 0; i < 3; i++)
            {
                returnMoment[i] = fourierComponent.mutable_at(i);
            }
            return returnMoment;
        }

        case 2 :  // Antiferromagnet
        {
            // Evaluate k dot T, where T is the position vector
            double kDotT = propagationVector.mutable_at(0) * x + propagationVector.mutable_at(1) * y + propagationVector.mutable_at(2) * z;

            for (int i = 0; i < 3; i++)
            {
                returnMoment[i] = fourierComponent.mutable_at(i) * cos(kDotT - M_PI_2);
            }
            return returnMoment;
        }

        case 3 :  // Single-k helical state
        {
            double qz = 2 * M_PI / propagationWavelength;

            returnMoment[0] = -0.5 * cos(qz * z);
            returnMoment[1] = -0.5 * sin(qz * z);
            returnMoment[2] = 0;

            // Account for the fact that a moment of 0.25 mu_B is used
            for (int i = 0; i < returnMoment.size(); i++)
            {
                returnMoment[i] = 0.25 * returnMoment[i];
            }

            return returnMoment;
        }

        case 4 :  // Triple-k "skyrmion" state
        {
            double F1 = 2 * M_PI / propagationWavelength;
            double F2 = 2 * M_PI / propagationWavelength;
            double F3 = 2 * M_PI / propagationWavelength;

            std::vector<double> q1 = {-F1, 0, 0};
            std::vector<double> q2 = {0.5 * F2, -F2 * sqrt(3) / 2, 0};
            std::vector<double> q3 = {0.5 * F3, F3 * sqrt(3) / 2, 0};

            double q1DotR = q1[0] * x + q1[1] * y + q1[2] * z;
            double q2DotR = q2[0] * x + q2[1] * y + q2[2] * z;
            double q3DotR = q3[0] * x + q3[1] * y + q3[2] * z;


            returnMoment[0] = cos(q1DotR + M_PI) + cos(q2DotR + M_PI) + cos(q3DotR + M_PI);
            returnMoment[1] = sin(q1DotR + M_PI) + sin(q2DotR + M_PI) + sin(q3DotR + M_PI);
            returnMoment[2] = 0;

            // Normalise, and multiply by the required magnitude (0.25 mu_B in Tom's paper)
            double magnitude = 0;
            for (int i = 0; i < returnMoment.size(); i++)
            {
                magnitude = magnitude + pow(returnMoment[i], 2);
            }
            magnitude = sqrt(magnitude);

            for (int i = 0; i < returnMoment.size(); i++)
            {
                returnMoment[i] = 0.25 * returnMoment[i] / magnitude;
            }

            return returnMoment;
        }

    }
}
