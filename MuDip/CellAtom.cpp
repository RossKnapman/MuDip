//
// Created by Ross Knapman on 02/08/2018.
//

#include "CellAtom.h"

CellAtom::CellAtom(double x, double y, double z, bool flipped)
{
    setX(x);
    setY(y);
    setZ(z);
    setFlipped(flipped);
}