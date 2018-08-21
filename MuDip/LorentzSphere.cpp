#include "LorentzSphere.h"
#include <iostream>
#include <fstream>


LorentzSphere::LorentzSphere(double xIn, double yIn, double zIn, Sample sampleIn, double radiusIn) : sample(sampleIn)
{
    setX(xIn);
    setY(yIn);
    setZ(zIn);
    setSample(sampleIn);
    setRadius(radiusIn);

    double latticeConstant = sample.getA();

    // Set up the dipoles within the sphere
    // First loop through unit cells
    for (double i = x - radius; i < x + radius + 1; i++)
    {
        for (double j = y - radius; j < y + radius + 1; j++)
        {
            for (double k = z - radius; k < z + radius + 1; k++)
            {
                // Loop through atoms within each unit cell, create dipole
                std::vector<CellAtom> atoms = sample.getAtoms();
                for (int atomIndex = 0; atomIndex < atoms.size(); atomIndex++)
                {
                    double dipoleXPos = i + atoms[atomIndex].getX() - fmod(x, 1);  // The fmod part brings the origin to the corner of the unit cell
                    double dipoleYPos = j + atoms[atomIndex].getY() - fmod(y, 1);
                    double dipoleZPos = k + atoms[atomIndex].getZ() - fmod(z, 1);

                    // Ensure the dipole is inside the sphere (instead of a cube)
                    if (sqrt(pow(dipoleXPos - x, 2) + pow(dipoleYPos - y, 2) + pow(dipoleZPos - z, 2)) < radius)
                    {
                        std::vector<double> moment = sample.getMomentField().getMoment(dipoleXPos, dipoleYPos, dipoleZPos);

                        if (atoms[atomIndex].getFlipped())  // If the atom is to be flipped, flip the moment
                        {
                            for (int i = 0; i < moment.size(); i++)
                            {
                                moment[i] = -moment[i];
                            }
                        }
                        Dipole *dipole = new Dipole(dipoleXPos, dipoleYPos, dipoleZPos, moment, latticeConstant);
                        dipoles.push_back(*dipole);
                    }
                }
            }
        }
    }
}


/**
*   Evaluate the dipole field by summing up the contributions from the individual
*   dipoles within the Lorentz sphere.
*   @return The dipole field as a vector.
*/
std::vector<double> LorentzSphere::calculateDipoleField()
{
    std::vector<double> Bdip(3);

    // Loop through dipoles list and get field from each
    for (int i = 0; i < dipoles.size(); i++)
    {
        std::vector<double> singleDipoleField = dipoles[i].calculateField(x, y, z);
        Bdip[0] = Bdip[0] + singleDipoleField[0];
        Bdip[1] = Bdip[1] + singleDipoleField[1];
        Bdip[2] = Bdip[2] + singleDipoleField[2];
    }

    return Bdip;
}


/**
*   Evaluate the Lorentz field for the Lorentz sphere.
*   @return The Lorentz field as a vector.
*/
std::vector<double> LorentzSphere::calculateLorentzField()
{
    std::vector<double> Blor(3);
    std::vector<double> m(3);  // Sum of magnetic moments in Lorentz sphere

    // Loop thorugh dipoles list and get the magnetic moment of each
    for (int i = 0; i < dipoles.size(); i++)
    {
        std::vector<double> localMoment = dipoles[i].getMoment();  // The moment of the individual atom within the loop

        // Add the vectors
        for (int mIndex = 0; mIndex < localMoment.size(); mIndex++)
        {
            m[mIndex] = m[mIndex] + localMoment[mIndex];  // This line causes the problem
        }
    }

    // Use this to calculate the Lorentz field, B = (mu_0 / 3) * Sum of moments in Lorentz sphere / Volume of Lorentz sphere
    for (int i = 0; i < Blor.size(); i++)
    {
        // Note that here we convert radius units from unit cells to Angstroms, i.e. multiply by (1 / a * 10^-10)^3, where a = lattice constant
        // We also convert m from Bohr magnetons to J/T
        Blor[i] = (constants::mu_0 / 3) * (3 / (4 * M_PI * pow(radius, 3))) * m[i] * pow((sample.getA() * pow(10, -10)), -3) * constants::bohrMagneton;
    }

    return Blor;
}
