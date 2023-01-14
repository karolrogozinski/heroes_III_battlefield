#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "hero.h"

typedef std::shared_ptr<Hero> HPtr;
typedef std::pair<int, int> cordsT;

class Battlefield
{
    HPtr mEnemy;
    HPtr mPlayer;
    const int mSize = 11;

    public:
        Battlefield(HPtr player, HPtr enemy);
        Battlefield(Hero& player, Hero& enemy);

        void generateDefUnitsCords(HPtr Hero, bool leftSide);

        bool MoveStack(cordsT startCords,
                       cordsT finalCords,
                       bool isPlayer);
        bool Attack(cordsT itsCords, cordsT enemyCords, bool isPlayer);

        std::vector<cordsT> GetAllOccupiedCords();
        
        std::vector<cordsT> GetPossibleMoveCords(
            cordsT cords,
            bool isPlayer); 

    int getSize() {return mSize;}
    HPtr getPlayer() {return mPlayer;}
    HPtr getEnemy() {return mEnemy;}
};