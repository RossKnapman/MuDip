//
// Created by Ross Knapman on 30/07/2018.
//

#ifndef INC_3DDIPOLEFIELD_LORENTZSPHERE_H
#define INC_3DDIPOLEFIELD_LORENTZSPHERE_H

#include "Dipole.h"
#include "Sample.h"


class LorentzSphere

{
private:

    double x;
    double y;
    double z;
    Sample sample;
    double radius;  // Radius of Lorentz sphere in unit cells (i.e. units of a of UnitCell)

    std::vector<Dipole> dipoles;

public:

    LorentzSphere(double x, double y, double z, Sample sampleIn, double radiusIn);

    // Setters
    void setX(double xIn) { x = xIn; }
    void setY(double yIn) { y = yIn; }
    void setZ(double zIn) { z = zIn; }
    void setSample(Sample sampleIn) { sample = sampleIn; }
    void setRadius(double radiusIn) { radius = radiusIn; }


    // Getters
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    double getRadius() { return radius; }
    std::vector<Dipole> getDipoles() { return dipoles; }

    std::vector<double> calculateDipoleField();
    std::vector<double> calculateLorentzField();

};


#endif //INC_3DDIPOLEFIELD_LORENTZSPHERE_H
