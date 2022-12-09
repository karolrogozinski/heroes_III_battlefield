#include "./headers/hero.h"
#include "./headers/ability.h"

void Hero::AddAbility(const Ability& Ab)
{
    Ability* NewAbility = new Ability(Ab._a); 
    _abilities.push_back(NewAbility);
}
