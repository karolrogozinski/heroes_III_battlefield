#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "hero.h"

typedef std::shared_ptr<Hero> HPtr;
typedef std::pair<int, int> cordsT;

class Battle
{
    HPtr mEnemy;
    HPtr mPlayer;
    const int mSize = 11;

    public:
        Battle(HPtr player, HPtr enemy);
        Battle(Hero& player, Hero& enemy);

        HPtr getPlayer() {return mPlayer;}
        HPtr getEnemy() {return mEnemy;}
        const int getSize() {return mSize;}

        void generateDefUnitsCords(HPtr Hero, bool leftSide);

        bool MoveStack(cordsT startCords, cordsT finalCords, bool isPlayer);
        bool CheckBasicAttackPoss(cordsT itsCords, cordsT opponentCords, bool isPlayer);
        std::pair<bool, bool> PerformAttack(cordsT itsCords, cordsT opponentCords,
                                            bool isPlayer, int attackingStackType);

        std::vector<cordsT> GetAllOccupiedCords();
        std::vector<cordsT> GetPossibleMoveCords(cordsT cords, bool isPlayer); 
        std::pair<bool, cordsT> GetPossibleMoveCords(cordsT itsCords,
                                                     cordsT opponentCords,
                                                     bool isPlayer);
};