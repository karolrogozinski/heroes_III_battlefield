#include <iostream>
#include "headers/hero.h"
// #include "../src/headers/controller.h"

int main()
{
    Hero h = Hero("dupa", 2);
    Stack s1 = Stack(1, 2, 3, 4, 5, 6);
    Stack s2 = Stack(7, 8, 9, 10, 11, 12);
    
    h.getForces().push_back(s1);

    std::cout<<h.getForces()[0].getSpeed()<<std::endl;
    std::cout<<h.getForces()[0].getAttack()<<std::endl;

    h.getForces()[0].setSpeed(666);
    std::cout<<h.getForces()[0].getSpeed()<<std::endl;


    return 0;
}