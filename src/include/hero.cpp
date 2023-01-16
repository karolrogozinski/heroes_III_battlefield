#include "../headers/hero.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
namespace py = pybind11;
PYBIND11_MODULE(hero, m)
{
    py::class_<Hero, std::shared_ptr<Hero>>(m, "Hero")
        .def(py::init<>())
        .def(py::init<std::string, bool>())

        .def("get_name", &Hero::getName)
        .def("get_is_player", &Hero::getIsPlayer)
        .def("get_forces", &Hero::getForces)

        .def("set_name", &Hero::setName)
        .def("set_is_player", &Hero::setIsPlayer)
        .def("set_forces", &Hero::setForces)

        .def("get_stack", &Hero::GetStack)
        .def("add_stack", &Hero::AddStack);
}

Stack& Hero::GetStack(std::pair<int, int> cords)
{
    for (Stack& stack: mForces)
    {
        if (stack.getCords() == cords){
            return stack;
        }
    }
    Stack failStack = Stack();
    return failStack;
}

void Hero::AddStack(Stack newStack)
{
    // for (Stack stack: mForces)
    // {
    //     if (stack.getID() == newStack.getID())
    //         stack.AddUnits(newStack);
    //         return;
    // }

    mForces.push_back(newStack);
}