#include <iostream>
#include "headers/battle.h"

int main()
{
    Hero h1 = Hero("hero1", true);
    Stack s1 = Stack(1, 2, 3, 4, 5, 6);
    Stack s2 = Stack(7, 8, 9, 10, 11, 12);
    s1.setCords({1, 7});
    h1.AddStack(s1);
    h1.AddStack(s2);

    Hero h2 = Hero("hero2", false);
    Stack s3 = Stack(2, 3, 4, 5, 6, 7);
    Stack s4 = Stack(3, 4, 5, 6, 7,8 );
    h2.AddStack(s3);
    h2.AddStack(s4);

    Battle b = Battle(h1, h2);
    bool result = b.MoveStack({1, 7}, {2, 2}, true);

    return 0;
}