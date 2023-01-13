#include "./headers/stack.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(stack, m)
{
    py::class_<Stack>(m, "Stack")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<const Stack&)
        .def("AddUnit", &Stack::AddUnit)
        .def("AddUnit", &Stack::AddUnit(UPtr))
        .def("AddUnit", &Stack::AddUnit(Unit*))
        .def("BeAttacked", &Stack::BeAttacked(float))
        .def("Attack", &Stack::Attack(Stack&))
        .def("Attack", &Stack::Attack(std::shared_ptr<Stack>))
        .def("getUnits", &Stack::getUnits())
        .def("getSize", &Stack::getSize())
        .def("getProtection", &Stack::getAttack())
        .def("getID", &Stack::getID())
        .def("AddUnit", &Stack::AddUnit())
        .def("AddUnit", &Stack::AddUnit(UPtr))
        .def("AddUnit", &Stack::AddUnit(Unit*))
        .def("BeAttack", &Stack::BeAttacked(float))
        .def("Attack", &Stack::(Stack&))
        .def("Attack", &Stack::(std::shared_ptr<Stack>))
}


void Stack::AddUnit()
{
    mUnits.push_back(UPtr(new Unit()));
    mSize += 1;
}

void Stack::AddUnit(UPtr unit)
{
    mUnits.push_back(unit);
    mSize += 1;
    if (mProtection == 0)
    {
    mProtection = unit->getProtection();
    mAttack = unit->getAttack();
    }
}

void Stack::AddUnit(Unit* unit)
{
    AddUnit(UPtr(unit));
}

void Stack::BeAttacked(float damage)
{
    int toRemove = 0;
    float tempDif;
    for (UPtr unit: mUnits)
    {
        if (damage >= unit->getHP())
        {
            damage -= unit->getHP();
            toRemove += 1;
        }
        else if (damage < unit->getHP() && damage > 0)
        {
            unit->GetInjured(damage);
            damage = 0;
        }
        else break;
    }

    for (int i = 0; i < toRemove; ++i)
    {
        mUnits.erase(mUnits.begin());
    }
}


bool Stack::Attack(Stack& stack)
{
    std::vector<UPtr> enemyUnits = stack.getUnits();
    int protDif = mAttack - stack.getProtection();
    if (protDif < 0)
    {
        protDif = 0;
    }
    float percAddition = protDif * 0.05;
    if (percAddition > 3.)
    {
        percAddition = 3.;
    }
    float sumDamage = 0.;
    for (UPtr unit: mUnits)
    {
        sumDamage += unit->GenerateDamage();
    }
    sumDamage += percAddition * sumDamage;

    stack.BeAttacked(sumDamage);

    if (stack.getUnits().size() == 0)
    {
        return true;
    }
    return false;
}

bool Stack::Attack(std::shared_ptr<Stack> stack)
{
    const float multiplier = 0.05;
    std::vector<UPtr> enemyUnits = stack->getUnits();
    int protDif = mAttack - stack->getProtection();
    if (protDif < 0)
    {
        protDif = 0;
    }
    float percAddition = protDif * multiplier;
    if (percAddition > 3.)
    {
        percAddition = 3.;
    }
    float sumDamage = 0.;
    for (UPtr unit: mUnits)
    {
        sumDamage += unit->GenerateDamage();
    }
    sumDamage += percAddition * sumDamage;

    stack->BeAttacked(sumDamage);

    if (stack->getUnits().size() == 0)
    {
        return true;
    }
    return false;
}

bool operator== (const Stack& lhs, const Stack& rhs)
{
    return lhs.mID == rhs.mID &&
        lhs.mUnits == rhs.mUnits &&
        lhs.mSize == rhs.mSize &&
        lhs.mProtection == rhs.mProtection &&
        lhs.mAttack == rhs.mAttack;
}