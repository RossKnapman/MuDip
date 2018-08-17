#include "Cu2OSeO3.h"
#include "../Sample.h"


// We must pass this crystal's lattice constant a = 8.925 Angstroms to the base constructor
Cu2OSeO3::Cu2OSeO3(MomentField momentFieldIn) : Sample(8.92500, momentFieldIn)
{

    setMomentField(momentFieldIn);

    CellAtom *atom1 = new CellAtom(0.886000, 0.886000, 0.886000, true);
    atoms.push_back(*atom1);

    CellAtom *atom2 = new CellAtom(0.614000, 0.114000, 0.386000, true);
    atoms.push_back(*atom2);

    CellAtom *atom3 = new CellAtom(0.386000, 0.614000, 0.114000, true);
    atoms.push_back(*atom3);

    CellAtom *atom4 = new CellAtom(0.114000, 0.386000, 0.614000, true);
    atoms.push_back(*atom4);

    CellAtom *atom5 = new CellAtom(0.133500, 0.121100, 0.871900);
    atoms.push_back(*atom5);

    CellAtom *atom6 = new CellAtom(0.871900, 0.133500, 0.121100);
    atoms.push_back(*atom6);

    CellAtom *atom7 = new CellAtom(0.121100, 0.871900, 0.133500);
    atoms.push_back(*atom7);

    CellAtom *atom8 = new CellAtom(0.366500, 0.878900, 0.371900);
    atoms.push_back(*atom8);

    CellAtom *atom9 = new CellAtom(0.371900, 0.366500, 0.878900);
    atoms.push_back(*atom9);

    CellAtom *atom10 = new CellAtom(0.878900, 0.371900, 0.366500);
    atoms.push_back(*atom10);

    CellAtom *atom11 = new CellAtom(0.866500, 0.621100, 0.628100);
    atoms.push_back(*atom11);

    CellAtom *atom12 = new CellAtom(0.628100, 0.866500, 0.621100);
    atoms.push_back(*atom12);

    CellAtom *atom13 = new CellAtom(0.621100, 0.628100, 0.866500);
    atoms.push_back(*atom13);

    CellAtom *atom14 = new CellAtom(0.633500, 0.378900, 0.128100);
    atoms.push_back(*atom14);

    CellAtom *atom15 = new CellAtom(0.128100, 0.633500, 0.378900);
    atoms.push_back(*atom15);

    CellAtom *atom16 = new CellAtom(0.378900, 0.128100, 0.633500);
    atoms.push_back(*atom16);
}
