//
// Created by Ross Knapman on 25/07/2018.
//

#ifndef INC_3DDIPOLEFIELD_DIPOLEFIELD_H
#define INC_3DDIPOLEFIELD_DIPOLEFIELD_H

#include "Dipole.h"


class DipoleField
{
private:
    std::vector<Dipole> dipoles;
    double separation;  // Separation between dipoles
    double radius;  // Radius of Lorentz sphere
    double moment;  // Magnitude of each magnetic moment

public:
    DipoleField(double separation, double radius, double moment);
    std::vector<Dipole> getDipoles() { return dipoles; }
};


#endif //INC_3DDIPOLEFIELD_DIPOLEFIELD_H
