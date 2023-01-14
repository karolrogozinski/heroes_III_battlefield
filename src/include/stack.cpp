#pragma once
#include "../headers/stack.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
namespace py = pybind11;
PYBIND11_DECLARE_HOLDER_TYPE(Stack, std::shared_ptr<Stack>)
// PYBIND11_DECLARE_HOLER_TYPE(Stack, std::shared_ptr<Unit>)
PYBIND11_MODULE(stack, m)
{
    py::class_<Stack>(m, "Stack")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<int, int, unsigned int, int, int, int, int>())

        .def("getID", &Stack::getID)
        .def("getType", &Stack::getType)
        .def("getHP", &Stack::getHP)
        .def("getUnitHP", &Stack::getUnitHP)
        .def("getSize", &Stack::getSize)
        .def("getSpeed", &Stack::getSpeed)
        .def("getProtection", &Stack::getProtection)
        .def("getAttack", &Stack::getAttack)
        .def("getDamage", &Stack::getDamage)
        .def("getCords", &Stack::getCords)

        .def("setID", &Stack::setID)
        .def("setType", &Stack::setType)
        .def("setHP", &Stack::setHP)
        .def("setUnitHP", &Stack::setUnitHP)
        .def("setSize", &Stack::setSize)
        .def("setSpeed", &Stack::setSpeed)
        .def("setProtection", &Stack::setProtection)
        .def("setAttack", &Stack::setAttack)
        .def("setCords", &Stack::setCords)
        
        .def("BeAttacked", &Stack::BeAttacked)
        .def("Attack", &Stack::Attack)
        .def("AddUnits", &Stack::AddUnits)
        .def("GenerateStackDamage", &Stack::GenerateStackDamage);
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


bool Stack::Attack(SPtr stackPtr)
{
    const float multiplier = 0.05;
    float finalDamage = multiplier * mSize  * GenerateStackDamage() *
                        (mAttack - stackPtr->getProtection());
    return stackPtr->BeAttacked(finalDamage);
}

bool operator== (const Stack& lhs, const Stack& rhs)
{
    return lhs.mID == rhs.mID &&
        lhs.mSize == rhs.mSize &&
        lhs.mProtection == rhs.mProtection &&
        lhs.mAttack == rhs.mAttack;
}

void Stack::AddUnits(SPtr stackPtr)
{
    mSize += stackPtr->getSize();
    mHP += mUnitHP * stackPtr->getSize();
}
