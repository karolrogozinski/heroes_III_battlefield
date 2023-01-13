#include "./headers/unit.h"
#include "./headers/randomGenerator.h"


void Unit::GetInjured(float damage)
{
    mHP -= damage;
}

int Unit::GenerateDamage()
{
    return RandomGenerator::getInstance().GetIntInRange(mDamage.first, mDamage.second);
}