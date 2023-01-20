#include "../headers/Stack.h"

bool Stack::BeAttacked(int damage)
{
    int deadUnits;
    int recdDamage = 0;
    for (deadUnits = 0; deadUnits < mSize; ++deadUnits)
    {
        if (!deadUnits)
            recdDamage += mHP - (mSize-1) * mUnitHP;
        else
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
    int finalDamage =  mSize  * GenerateStackDamage() + multiplier *
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
