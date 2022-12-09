#include "./headers/hero.h"

void CHero::AddAbility(const CAbility& cGability)
{
    CAbility cNewAbility = cGability; 
    CAbilities.push_back(cNewAbility);
}

void CHero::Attack(CHero* cEnemy)
{
    int nDamage = cEnemy->nProtection - nAttack;
    if (nDamage < 0)
    {
        nDamage = -nDamage;
    }
    cEnemy->nHP -= nDamage;
};