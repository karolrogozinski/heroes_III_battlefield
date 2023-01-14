#pragma once
#include "./headers/stack.h"

// #include <pybind11/pybind11.h>
// #include <pybind11/stl.h>
// #include <pybind11/complex.h>
// #include <pybind11/functional.h>
// namespace py = pybind11;
// PYBIND11_DECLARE_HOLDER_TYPE(Stack, std::shared_ptr<Stack>)
// // PYBIND11_DECLARE_HOLER_TYPE(Stack, std::shared_ptr<Unit>)
// PYBIND11_MODULE(stack, m)
// {
//     py::class_<Stack>(m, "Stack")
//         .def(py::init<>())
//         .def(py::init<int>())
//         .def(py::init<int, int, int, int, int>())
//         .def("AddUnit", &Stack::AddUnit)
//         .def("BeAttacked", &Stack::BeAttacked)
//         .def("Attack", &Stack::Attack)
//         .def("getUnits", &Stack::getUnits)
//         .def("getSize", &Stack::getSize)
//         .def("getProtection", &Stack::getAttack)
//         .def("getID", &Stack::getID)
//         .def("BeAttack", &Stack::BeAttacked);
// }

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
    mSize -= deadUnits;

    return mSize < 0 ? true : false;
}

int GetPseudoRandom(std::pair<int, int> range)
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
