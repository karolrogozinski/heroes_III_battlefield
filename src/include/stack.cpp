#include "../headers/stack.h"

bool Stack::BeAttacked(float damage)
{
    int deadUnits;
    float recdDamage = 0;
    for (deadUnits = 0; deadUnits < mSize; ++deadUnits)
    {
        recdDamage += mUnitHP;
        if (recdDamage > damage)
        {
            recdDamage = damage;
            break;
        }
    }
    mHP -= recdDamage;
    mSize -= deadUnits;
    return mSize <= 0 ? true : false;
}

int GetPseudoRandom(cordsT range)
{
    int size = range.second - range.first + 1;
    int value = range.first + (std::rand() % size);
    return value;
}

int Stack::GenerateStackDamage()
{
    return GetPseudoRandom(mDamage);
}


bool Stack::Attack(Stack& stack)
{
    const float multiplier = 0.05;
    float finalDamage =  mSize  * GenerateStackDamage() + multiplier *
                        (mAttack - stack.getProtection());
    return stack.BeAttacked(finalDamage);
}

bool operator== (const Stack& lhs, const Stack& rhs)
{
    return lhs.mID == rhs.mID &&
        lhs.mSize == rhs.mSize &&
        lhs.mProtection == rhs.mProtection &&
        lhs.mAttack == rhs.mAttack;
}

void Stack::AddUnits(Stack stack)
{
    mSize += stack.getSize();
    mHP += mUnitHP * stack.getSize();
}
