#include "./headers/hero.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(hero, m)
{
    py::class_<Hero>(m, "Hero")
        .def(py::init<std::string, int, int, int, int>(), "name"_a, "attack"_a, "protection"_a, "level"_a = 0, "exp"_a = 0)
        .def("GetName", &Hero::GetName)
        .def("GetAttack", &Hero::GetAttack)
        .def("GetProtection", &Hero::GetProtection)
        .def("GetLevel", &Hero::GetLevel)
        .def("GetExp", &Hero::GetExp)
        .def("GetAbilities", &Hero::GetAbilities)

        .def("SetName", &Hero::SetName)
        .def("SetAttack", &Hero::SetAttack)
        .def("SetProtection", &Hero::SetProtection)
        .def("SetLevel", &Hero::SetLevel)
        .def("SetExp", &Hero::SetExp)

        .def("AddExp", &Hero::AddExp)
        .def("AddAttack", &Hero::AddAttack)
        .def("AddProtection", &Hero::AddProtection)
        .def("AddAbility", &Hero::AddAbility);
}


void Hero::AddAbility(const Ability& Ab)
{
    APtr NewAbility = APtr(new Ability(Ab._a)); 
    _abilities.push_back(NewAbility);
}
