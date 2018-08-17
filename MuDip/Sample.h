#ifndef INC_3DDIPOLEFIELD_SAMPLE_H
#define INC_3DDIPOLEFIELD_SAMPLE_H

#include <vector>
#include "CellAtom.h"
#include "MomentField.h"


// We do not want to instantiate this class directly, rather it acts as the base class
// for specific crystals in the "Crystals" directory


class Sample
{

protected:
    std::vector<CellAtom> atoms;
    double a;
    MomentField momentField;

public:

    Sample(double aIn, MomentField momentFieldIn);

    // Setters
    void setA(double aIn) { a = aIn; }
    void setMomentField(MomentField momentFieldIn) { momentField = momentFieldIn; }

    // Getters
    std::vector<CellAtom> getAtoms() { return atoms; }
    double getA() { return a; }
    MomentField getMomentField() { return momentField; }

    std::vector<double> getDipoleField(double x, double y, double z, double radius);  // x, y, z in unit cells, as well as Lorentz sphere radius
    std::vector<double> getLorentzField(double x, double y, double z, double radius);
    std::vector<double> getTotalField(double x, double y, double z, double radius);


};


#endif //INC_3DDIPOLEFIELD_SAMPLE_H
