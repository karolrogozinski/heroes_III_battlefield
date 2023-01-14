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

void Hero::AddForce(Stack& stack)
{
    SPtr StackPtr = SPtr(new Stack(stack));
    mForces.push_back(StackPtr);
}

void Hero::AddGood(unsigned int i, unsigned int value)
{
    if (i != 0)
    {
        mGoods[i] += value;
    } else {
        int expDiff = mLvlExpLimit - mExp;
        bool nextLevel = expDiff < value;
        if (nextLevel)
        {
            mLevel += 1;
            mExp = value - expDiff;
            mLvlExpLimit = CountNewExpLimit();
        } else {
            mExp += value;
        }
    }
}

void Hero::ReduceGood(unsigned int i, unsigned int value)
{
    if (i = 0) {return;}
    if (mGoods[i] < value)
    {
        mGoods[i] = 0;
    } else {
        mGoods[i] -= value;
    }
}

int Hero::CountNewExpLimit()
{
    double newLimit = pow(mLevel, 2) * 25;
    return (int) newLimit;
}

SPtr Hero::getStack(std::pair<int, int> cords)
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
            stackPtr->ConcatStack(newStackPtr);
            return;
    }

    mForces.push_back(newStackPtr);
}