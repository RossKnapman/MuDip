/**
*   @file Dipole.h
*   @brief Stores information about individual dipole, and allows the evaluation
*   of its resulting field at an arbitrary point.
*   @author Ross Knapman
*   @date 21/08/2018
*/


#ifndef INC_3DDIPOLEFIELD_DIPOLE_H
#define INC_3DDIPOLEFIELD_DIPOLE_H

#include <vector>
#include "Constants.h"


class Dipole
{
private:
    double x;  // Position in unit cells
    double y;
    double z;
    std::vector<double> moment;  // Moment vector in Bohr magnetons
    double latticeConstant;  // The lattice constant in Angstroms

public:
    Dipole(double xIn, double yIn, double zIn, std::vector<double> momentIn, double latticeConstantIn);

    // Setters
    void setX(double xIn) { x = xIn; }
    void setY(double yIn) { y = yIn; }
    void setZ(double zIn) { z = zIn; }
    void setMoment(std::vector<double> momentIn) { moment = momentIn; }
    void setLatticeConstant(double latticeConstantIn) { latticeConstant = latticeConstantIn; }

    // Getters
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    std::vector<double> getMoment() { return moment; }
    double getLatticeConstant() { return latticeConstant;}

    // Misc.
    std::vector<double> calculateField(double targetX, double targetY, double targetZ);
};


#endif //INC_3DDIPOLEFIELD_DIPOLE_H
