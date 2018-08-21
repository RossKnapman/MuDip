#include "Dipole.h"
#include <iostream>
#include <numeric>
#include "Constants.h"


// Dipole constructor
Dipole::Dipole(double xIn, double yIn, double zIn, std::vector<double> momentIn, double latticeConstantIn)
{
    setX(xIn);
    setY(yIn);
    setZ(zIn);
    setMoment(momentIn);
    setLatticeConstant(latticeConstantIn);
}


/**
*   Calculate the field due to a single dipole at an arbitrary point.
*   @param x The x-position of the point at which we wish to evaluate the dipole field.
*   @param y The y-position of the point at which we wish to evaluate the dipole field.
*   @param z The z-position of the point at which we wish to evaluate the dipole field.
*   @return The dipole magnetic field as a vector.
*/
std::vector<double> Dipole::calculateField(double targetX, double targetY, double targetZ)
{

    // Position vector of point at which field evaluated (inputs in unit cells, but converted to Angstroms)
    std::vector<double> R{targetX * latticeConstant, targetY * latticeConstant, targetZ * latticeConstant};

    // Position vector of dipole (in unit cells)
    std::vector<double> r_d{x * latticeConstant, y * latticeConstant, z * latticeConstant};

    // Vector pointing from dipole to point where field evaluated
    std::vector<double> r;
    for (int i = 0; i < R.size(); i++)
    {
        r.push_back(r_d[i] - R[i]);
    }

    std::vector<double> B(r.size());

    // Calculate the magnitude of r
    double rMag = 0;
    for (int i = 0; i < r.size(); i++)
    {
        rMag = rMag + pow(r[i], 2);
    }
    rMag = sqrt(rMag);

    // Get the r unit vector
    std::vector<double> rUnit(r.size());

    for (int i = 0; i < rUnit.size(); i++)
    {
        rUnit[i] = r[i] / rMag;
    }

    // Evaluate the m dot rHat inner product in the B-field expression
    double mrInnerProd = 0;

    for (int i = 0; i < moment.size(); i++)
    {
        mrInnerProd = mrInnerProd + moment[i] * rUnit[i];
    }

    for (int i = 0; i < r.size(); i++)
    {
        // Preceeding 10^23 is the mu_0 / 4pi = 10^-7, multiplied by 1/Angstrom^3 = 10^30
        // May be more efficient to just scale the units at the end, rather than with each dipole
        B[i] = pow(10, 23) * constants::bohrMagneton * pow(rMag, -3) * (3 * mrInnerProd * rUnit[i] - moment[i]);
    }

    return B;
}
