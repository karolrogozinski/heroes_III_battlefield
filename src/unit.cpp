#include "./headers/unit.h"

int Unit::GenerateDamage()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(_damage.first, _damage.second);
    return distr(gen);
}

void Unit::GetInjured(float damage)
{
    _hp -= damage;
}
