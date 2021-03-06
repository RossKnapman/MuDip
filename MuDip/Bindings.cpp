#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <string>
#include "MomentField.h"
#include "SpectrumCreator.h"
#include "VectorFieldCreator.h"
#include "Crystals/Cu2OSeO3.h"
#include "Sample.h"

namespace py = pybind11;

PYBIND11_MODULE(MuDip, m)
{
    py::class_<MomentField>(m, "MomentField")  // Should add all functions really
        // Constructors
        .def(py::init<py::array_t<double>>())
        .def(py::init<py::array_t<double>, double, py::array_t<double> >())
        .def(py::init<double, std::string>());

    py::class_<Sample>(m, "Sample")  // The user shouldn't instantiate this but its child classes (only Cu2OSeO3 at present)
        .def(py::init<double, MomentField>())
        .def("getDipoleField", &Sample::getDipoleField)
        .def("getLorentzField", &Sample::getLorentzField)
        .def("getTotalField", &Sample::getTotalField);

    py::class_<Cu2OSeO3, Sample>(m, "Cu2OSeO3")
        .def(py::init<MomentField>());

    py::class_<SpectrumCreator>(m, "SpectrumCreator")
        .def(py::init<MomentField, Sample, py::array_t<double>,
          int, int, int, int, py::array_t<double>>())
        .def("outputSpectrum", &SpectrumCreator::outputSpectrum);

    py::class_<VectorFieldCreator>(m, "VectorFieldCreator")
      .def(py::init<MomentField, Sample, py::array_t<double>,
      int, int, int, int, py::array_t<double>, double>())
      .def("outputBField", &VectorFieldCreator::outputBField)
      .def("outputMField", &VectorFieldCreator::outputMField);
};
