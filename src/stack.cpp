#include "./headers/stack.h"


void Stack::AddUnit()
{
    _units.push_back(UPtr(new Unit()));
    _size += 1;
}

void Stack::AddUnit(UPtr unit)
{
    _units.push_back(unit);
    _size += 1;
    if (_protection == 0)
    {
    _protection = unit->GetProtection();
    _attack = unit->GetAttack();
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
    for (UPtr unit: _units)
    {
        if (damage >= unit->GetHP())
        {
            damage -= unit->GetHP();
            toRemove += 1;
        }
        else if (damage < unit->GetHP() && damage > 0)
        {
            unit->GetInjured(damage);
            damage = 0;
        }
        else break;
    }

    for (int i = 0; i < toRemove; ++i)
    {
        _units.erase(_units.begin());
    }
}


void Stack::Attack(Stack& stack)
{
    std::vector<UPtr> enemyUnits = stack.GetUnits();
    int protDif = _attack - stack.GetProtection();
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
    for (UPtr unit: _units)
    {
        sumDamage += unit->GenerateDamage();
    }
    sumDamage += percAddition * sumDamage;

    stack.BeAttacked(sumDamage);
}