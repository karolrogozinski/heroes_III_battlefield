#include "./headers/hero.h"

void CHero::AddAbility(const CAbility& cGability)
{
    CAbility* cNewAbility = new CAbility(cGability.a); 
    CAbilities.push_back(cNewAbility);
}

