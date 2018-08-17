#ifndef INC_3DDIPOLEFIELD_CELLATOM_H
#define INC_3DDIPOLEFIELD_CELLATOM_H

#include "Dipole.h"


class CellAtom
{
private:
    double x;  // Position of the atom within the unit cell, in fractional coordinates
    double y;
    double z;
    bool flipped;  // Whether or not we flip the spin at that atom site

public:
    CellAtom(double x, double y, double z, bool flipped = false);

    // Setters
    void setX(double xIn) { x = xIn; }
    void setY(double yIn) { y = yIn; }
    void setZ(double zIn) { z = zIn; }
    void setFlipped(bool flippedIn) { flipped = flippedIn; }

    // Getters
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    bool getFlipped() { return flipped; }

};


#endif //INC_3DDIPOLEFIELD_CELLATOM_H
