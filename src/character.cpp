#include "./headers/character.h"


int CCharacter::rtsth(int a)
{
    return a;
}

void CCharacter::Attack(CCharacter* cEnemy)
{
    int nDamage = cEnemy->nProtection - nAttack;
    if (nDamage < 0)
    {
        cEnemy->nHP += nDamage;
    }

};