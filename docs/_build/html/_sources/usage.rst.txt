Usage
=====

Defining the Magnetic Structure
-------------------------------

There are currently four magnetic textures that may be defined. These are

* Ferromagnetic alignment
* Antiferromagnetic alignment
* A single-wavevector helical spin configuration, as described by T. Lancaster et. al. [1]_
* A triple-wavevector skyrmion-like spin configuration, as described by T. Lancaster et. al. [1]_

The initialisation of the magnetic structure depends on the arguments passed to its constructor. To define a ferromagnetically-aligned structure with spins parallel to the y-direction, one would run: ::

    from MuDip import MomentField
    import numpy as np
    fourierComponent = np.array([0, 1, 0])
    momentField = MomentField(fourierComponent)

For an antiferromagnetically-aligned structure for which the propagation is along the x-axis with a wavelength of 10 unit cells, and the spins are aligned parallel to the y-axis, one would run: ::

    from MuDip import MomentField
    import numpy as np
    propagationVector = np.array([1, 0, 0])
    wavelength = 10
    fourierComponent = np.array([0, 1, 0])
    momentField = MuDip.MomentField(propagationVector, wavelength, fourierComponent)

For the single-wavevector helical spin configuration, with a wavelength of 70 unit cells, one would run: ::

    from MuDip import MomentField
    wavelength = 70
    momentField = MomentField(wavelength, "singleK")

Similarly, for the triple-wavevector skyrmion-like spin configuration, with a skyrmion wavelengåth of 70 unit cells, one would run: ::

    from MuDip import MomentField
    wavelength = 70
    momentField = MomentField(wavelength, "tripleK")


Defining the Crystal Structure
------------------------------

Currently, the only crystal structure defined in MuDip is the Cu2OSeO3 crystal, which consists of 16 copper ions per unit cell, four of which have their moment flipped with respect to the general magnetic moment structure. To define the crystal, a :cpp:class:`MomentField` object is passed to the crystal as a argument, as in the following code: ::

    from MuDip import Cu2OSeO3
    crystal = Cu2OSeO3(momentField)


Obtaining the Magnetic Field at an Arbitrary Point within the Crystal
---------------------------------------------------------------------

To obtain the field due to the dipoles within a Lorentz sphere of radius 20 unit cells as a numpy array of the form [B_x, B_y, B_z], where B_i is the dipole magnetic field along the i-axis at position x = 3.4, y = 9.2, z = 10.1, where length units are specified in terms of unit cells, we would run the code: ::

    Bdip = crystal.getDipoleField(3.4, 9.2, 10.1, 20)

Similarly, for the Lorentz field: ::

    Blor = crystal.getLorentzField(3.4, 9.2, 10.1, 20)

And for the total (dipolar + Lorentz) field: ::

    Btot = crystal.getTotalField(3.4, 9.2, 10.1, 20)


Plotting the Magnetic Field within the Sample
---------------------------------------------

MuDip makes it relatively easy to obtain the projection of the magnetic field structure onto an arbitrary plane along the z-axis. After having defined the magnetic and crystal structures as previously described, we can create a :cpp:class:`VectorFieldCreator` object. ::

    muonPositions = np.array([[0.215, 0.700, 0.970]])
    startCell = 0
    endCell = 100
    resolution = 5
    radius = 2
    Bapplied = np.array([0, 0, 10])
    z = 0

    vectorFieldCreator = MuDip.VectorFieldCreator(momentField, crystal, muonPositions, startCell, endCell, resolution,
                                              radius, Bapplied, z)




References
----------

.. [1] Lancaster, T., Williams, R. C., Thomas, I. O., Xiao, F., Pratt, F. L., Blundell, S. J., Loudon, J. C., Hesjedal, T., Clark, S. J., Hatton, P. D., Ciomaga Hatnean, M., Keeble, D. S. & Balakrishnan, G. (2015). Transverse field muon-spin rotation signature of the skyrmion-lattice phase in Cu2OSeO3. Phys. Rev. B, 91, 224408.
