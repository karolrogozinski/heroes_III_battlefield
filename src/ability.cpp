#include "./headers/ability.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(ability, m)
{
    py::class_<Ability>(m, "Ability")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<const Ability &>())
        .def("getAbility", &Ability::getAbility);
}
