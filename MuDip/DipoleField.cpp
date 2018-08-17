//
// Created by Ross Knapman on 25/07/2018.
//

#include "DipoleField.h"

#include <iostream>
#include <cmath>


DipoleField::DipoleField(double separationIn, double radiusIn, double momentIn)
{
    moment = momentIn;
    radius = radiusIn;
    separation = separationIn;

    for (int i = -radius; i <= radius; i = i + separation)
    {
        for (int j = -radius; j <= radius; j = j + separation)
        {
            for (int k = -radius; k <= radius; k = k + separation)
            {
                if (sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2)) < radius)
                {
                    // Dipoles with their moment vector along z
                    Dipole *newDipole = new Dipole(i, j, k, 0, 0, 1);
                    dipoles.push_back(*newDipole);
                }
            }
        }
    }
}