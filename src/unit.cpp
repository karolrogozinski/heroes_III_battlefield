#include "./headers/unit.h"

void Unit::Attack(Unit* Enemy)
{
    int damage = Enemy->GetProtection() - _attack;
    if (damage < 0)
    {
        Enemy->SetHP(Enemy->GetHP() + damage);
    }

};