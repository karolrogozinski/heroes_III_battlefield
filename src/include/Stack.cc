#include "../headers/Stack.h"

bool Stack::beAttacked(int damage)
{
    int deadUnits;
    int recdDamage = 0;
    for (deadUnits = 0; deadUnits < size_; ++deadUnits)
    {
        if (!deadUnits)
            recdDamage += HP_ - (size_-1) * unitHP_;
        else
            recdDamage += unitHP_;
        if (recdDamage > damage)
        {
            recdDamage = damage;
            break;
        }
    }
    HP_ -= recdDamage;
    size_ -= deadUnits;
    return size_ <= 0 ? true : false;
}

int GetPseudoRandom(IntPair range)
{
    int size = range.second - range.first + 1;
    int value = range.first + (std::rand() % size);
    return value;
}

int Stack::generateStackDamage()
{
    return GetPseudoRandom(damage_);
}


bool Stack::attack(Stack& stack)
{
    const float multiplier = 0.05;
    int finalDamage =  size_  * generateStackDamage() + multiplier *
                        (attack_ - stack.getProtection());
    return stack.beAttacked(finalDamage);
}

bool operator== (const Stack& lhs, const Stack& rhs)
{
    return lhs.ID_ == rhs.ID_ &&
        lhs.size_ == rhs.size_ &&
        lhs.protection_ == rhs.protection_ &&
        lhs.attack_ == rhs.attack_;
}

void Stack::addUnits(Stack stack)
{
    size_ += stack.getSize();
    HP_ += unitHP_ * stack.getSize();
}
