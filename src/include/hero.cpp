#include "../headers/hero.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(hero, m)
{
    py::class_<Hero>(m, "Hero")
        .def(py::init<>())
        .def(py::init<std::string, bool>())
        .def(py::init<std::string, bool, std::vector<SPtr>())

        .def("getName", &Hero::getName)
        .def("getIsPlayer", &Hero::getIsPlayer)
        .def("getForces", &Hero::getForces)

        .def("setName", &Hero::setName)
        .def("setIsPlayer", &Hero::setIsPlayer)
        .def("setForces", &Hero::setForces)

        .def("GetStack", &Hero::GetStack)
        .def("AddStack", &Hero::AddStack);
}

SPtr Hero::GetStack(std::pair<int, int> cords)
{
    for (auto stack: mForces)
    {
        if (stack->getCords() == cords){
            return stack;
        }
    }
}

void Hero::AddStack(SPtr newStackPtr)
{
    for (SPtr stackPtr: mForces)
    {
        if (stackPtr->getID() == newStackPtr->getID())
            stackPtr->AddUnits(newStackPtr);
            return;
    }

    mForces.push_back(newStackPtr);
}