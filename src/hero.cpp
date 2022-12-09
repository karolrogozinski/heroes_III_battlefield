#include "./headers/hero.h"

void Hero::AddAbility(const Ability& Ab)
{
    APtr NewAbility = APtr(new Ability(Ab._a)); 
    _abilities.push_back(NewAbility);
}
