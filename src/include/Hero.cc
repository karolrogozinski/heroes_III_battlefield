#include "../headers/Hero.h"

Stack& Hero::getStack(std::pair<int, int> cords)
{
    for (Stack& stack: forces_)
    {
        if (stack.getCords() == cords){
            return stack;
        }
    }
    return forces_[0];
}

void Hero::addStack(Stack new_stack)
{
    forces_.push_back(new_stack);
}