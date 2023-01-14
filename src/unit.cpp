#include "./headers/unit.h"
#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
namespace py = pybind11;

PYBIND11_MODULE(unit, m)
{
    py::class_<Unit>(m, "Unit")
        .def(py::init<>())
        .def(py::init<std::string, float, int, int, std::pair<int, int>>())
        .def("getName", &Unit::getName)
        .def("getHP", &Unit::getHP)
        .def("getAttack", &Unit::getAttack)
        .def("getProtection", &Unit::getProtection)
        .def("getDamage", &Unit::getDamage)
        .def("GenerateDamage", &Unit::GenerateDamage);
}

void Unit::GetInjured(float damage)
{
    mHP -= damage;
}

int getPseudoRandom(int min, int max)
{
    int range = max - min + 1;
    int value = min + (std::rand() % range);
    return value;
}

int Unit::GenerateDamage()
{
    return getPseudoRandom(mDamage.first, mDamage.second);
}