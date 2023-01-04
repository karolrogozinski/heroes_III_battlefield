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
        .def("getName", &Hero::getName)
        .def("getAttack", &Hero::getAttack)
        .def("getProtection", &Hero::getProtection)
        .def("getLevel", &Hero::getLevel)
        .def("getExp", &Hero::getExp)
        .def("getAbilities", &Hero::getAbilities)

        .def("setName", &Hero::setName)
        .def("setAttack", &Hero::setAttack)
        .def("setProtection", &Hero::setProtection)
        .def("setLevel", &Hero::setLevel)
        .def("setExp", &Hero::setExp)

        .def("AddExp", &Hero::AddExp)
        .def("AddAttack", &Hero::AddAttack)
        .def("AddProtection", &Hero::AddProtection)
        .def("AddAbility", &Hero::AddAbility);
}


void Hero::AddAbility(const Ability& Ab)
{
    APtr NewAbility = APtr(new Ability(Ab.mValue)); 
    mAbilities.push_back(NewAbility);
}
