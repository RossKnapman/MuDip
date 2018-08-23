Improvements
======

Adding More Magnetic Structures
-------------------------------

The primary aim of this project was to investigate more magnetic field structures, so it is very likely that the user would wish to add investigate more sophisticated magnetic field patterns than the four provided. To do this, the user must:

#. Add the necessary constructor to the MomentField.cpp implementation file, if none of the existing constructors accept the required set of parameters. This new constructor must also be declared in the MomentField.h header file.

#. Update the MomentField.getType() function to return the corresponding magnetic field structure type.

#. Update the MomentField.getMoment() function. This is where the bulk of the code describing the moment field goes.

#. Add any new constructors to the Bindings.cpp file.

#. Re-install the module.


Adding  more
