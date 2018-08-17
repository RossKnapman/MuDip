cmake_minimum_required(VERSION 2.8.12)
project(MuDip)

# Set source directory
set(SOURCE_DIR "MuDip")

# Tell CMake that headers are also in SOURCE_DIR
# Important note: if a new crystal is added, it will need to be added to this file too
include_directories(${SOURCE_DIR})
set(SOURCES "${SOURCE_DIR}/CellAtom.cpp" "${SOURCE_DIR}/Dipole.cpp" "${SOURCE_DIR}/LorentzSphere.cpp"
"${SOURCE_DIR}/MomentField.cpp" "${SOURCE_DIR}/Sample.cpp" "${SOURCE_DIR}/SpectrumCreator.cpp"
"${SOURCE_DIR}/VectorFieldCreator.cpp" "${SOURCE_DIR}/Crystals/Cu2OSeO3.cpp")

# Generate Python module
add_subdirectory(lib/pybind11)
pybind11_add_module(MuDip ${SOURCES} "${SOURCE_DIR}/Bindings.cpp")
