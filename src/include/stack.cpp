#include "../headers/stack.h"
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
namespace py = pybind11;
PYBIND11_MODULE(stack, m)
{
    py::class_<Stack, std::shared_ptr<Stack>>(m, "Stack")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<int, int, unsigned int, int, int, int, int>())

        .def("get_id", &Stack::getID)
        .def("get_type", &Stack::getType)
        .def("get_hp", &Stack::getHP)
        .def("get_unit_hp", &Stack::getUnitHP)
        .def("get_size", &Stack::getSize)
        .def("get_speed", &Stack::getSpeed)
        .def("get_protection", &Stack::getProtection)
        .def("get_attack", &Stack::getAttack)
        .def("get_damage", &Stack::getDamage)
        .def("get_cords", &Stack::getCords)

        .def("set_id", &Stack::setID)
        .def("set_type", &Stack::setType)
        .def("set_hp", &Stack::setHP)
        .def("set_unit_hp", &Stack::setUnitHP)
        .def("set_size", &Stack::setSize)
        .def("set_speed", &Stack::setSpeed)
        .def("set_protection", &Stack::setProtection)
        .def("set_attack", &Stack::setAttack)
        .def("set_cords", &Stack::setCords)
        .def("set_damage", &Stack::setDamage)
        
        .def("be_attacked", &Stack::BeAttacked)
        .def("attack", &Stack::Attack)
        .def("add_units", &Stack::AddUnits)
        .def("generate_stack_damage", &Stack::GenerateStackDamage);
}

bool Stack::BeAttacked(float damage)
{
    int deadUnits;
    float recdDamage = 0;
    for (deadUnits = 0; deadUnits < mSize; ++deadUnits)
    {
        recdDamage += mUnitHP;
        if (recdDamage > damage)
        {
            recdDamage = damage;
            break;
        }
    }
    mHP -= recdDamage;
    mSize -= deadUnits;
    return mSize <= 0 ? true : false;
}

int GetPseudoRandom(cordsT range)
{
    int size = range.second - range.first + 1;
    int value = range.first + (std::rand() % size);
    return value;
}

int Stack::GenerateStackDamage()
{
    return GetPseudoRandom(mDamage);
}


bool Stack::Attack(Stack& stack)
{
    const float multiplier = 0.05;
    float finalDamage =  mSize  * GenerateStackDamage() + multiplier *
                        (mAttack - stack.getProtection());
    return stack.BeAttacked(finalDamage);
}

bool operator== (const Stack& lhs, const Stack& rhs)
{
    return lhs.mID == rhs.mID &&
        lhs.mSize == rhs.mSize &&
        lhs.mProtection == rhs.mProtection &&
        lhs.mAttack == rhs.mAttack;
}

void Stack::AddUnits(Stack stack)
{
    mSize += stack.getSize();
    mHP += mUnitHP * stack.getSize();
}
