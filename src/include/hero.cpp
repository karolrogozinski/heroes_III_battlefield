#include "../headers/hero.h"

Stack& Hero::GetStack(std::pair<int, int> cords)
{
    for (Stack& stack: mForces)
    {
        if (stack.getCords() == cords){
            return stack;
        }
    }
    return mForces[0];
}

void Hero::AddStack(Stack newStack)
{
    mForces.push_back(newStack);
}