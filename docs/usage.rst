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
    ferroMomentField = MomentField(fourierComponent)

For an antiferromagnetically-aligned structure for which the progagation is along the x-axis with a wavelength of 10 unit cells, and the spins are aligned parallel to the y-axis, one would run: ::

    from MuDip import MomentField
    import numpy as np
    propagationVector = np.array([1, 0, 0])
    wavelength = 10
    fourierComponent = np.array([0, 1, 0])
    antiFerroMomentField = MuDip.MomentField(propagationVector, wavelength, fourierComponent)


References
----------

.. [1] Lancaster, T., Williams, R. C., Thomas, I. O., Xiao, F., Pratt, F. L., Blundell, S. J., Loudon, J. C., Hesjedal, T., Clark, S. J., Hatton, P. D., Ciomaga Hatnean, M., Keeble, D. S. & Balakrishnan, G. (2015). Transverse field muon-spin rotation signature of the skyrmion-lattice phase in Cu2OSeO3. Phys. Rev. B, 91, 224408.
