#include <iostream>
// #include "../src/headers/hero.h"
// #include "../src/headers/stack.h"
// #include "../src/headers/controller.h"
#include "../src/headers/battlefield.h"
typedef std::shared_ptr<Hero> HPtr;

int main()
{
    HPtr hr1 = std::make_shared<Hero>(Hero());
    HPtr hr2 = std::make_shared<Hero>(Hero());
    // Hero hr1 = Hero();
    // Hero hr2 = Hero();
    Stack stack = Stack(2137);
    std::vector<UPtr> units;
    Unit* u1 = new Unit("u1", 21.37, 5, 2, {2, 7});
    Unit* u2 = new Unit("u2", 73.12, 6, 3, {3, 8});
    Unit* u3 = new Unit("u3", 32.48, 7, 4, {4, 9});
    Stack stack2 = Stack();
    stack2.AddUnit(UPtr(u1));
    stack2.AddUnit(UPtr(u2));
    stack2.AddUnit(UPtr(u3));
    SPtr sPtr = std::make_shared<Stack>(stack2);
    std::pair<int, int> cords = {1, 2};
    stack.setCords(cords);
    for (int i =0; i<7; ++i)
    {
        SPtr stack2 = std::make_shared<Stack>(Stack(i));
        Stack stack = Stack(i);
        hr1->AddForce(stack);
    }
    // hr1->AddStack(sPtr);
    // hr1->AddStack(sPtr);
    Battlefield bf = Battlefield(hr1, hr2);
    // for (auto dupa : bf.getPlayer()->getForces())
    // {
    //     std::cout<<dupa->getCords().first<<std::endl;
    //     std::cout<<dupa->getCords().second<<std::endl;
    //     std::cout<<std::endl;
    // }
    // // std::cout<<bf.getPlayer()->getForces()[1]->getCords().second<<std::endl;
    // std::cout<<bf.getSize()<<std::endl;
    // std::cout<<bf.GetAllOccupiedCords().size()<<std::endl;
    // bf.MoveStack

    return 0;
}