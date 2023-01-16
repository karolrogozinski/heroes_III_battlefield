#include "../headers/hero.h"

Stack& Hero::GetStack(std::pair<int, int> cords)
{
    for (Stack& stack: mForces)
    {
        if (stack.getCords() == cords){
            return stack;
        }
    }
    Stack failStack = Stack();
    return failStack;
}

void Hero::AddStack(Stack& newStack)
{
    mForces.push_back(newStack);
}
