#include "./headers/pickup.h"

void Pickup::Use(Hero& hero)
{
    hero.AddGood(mID, mValue);
}