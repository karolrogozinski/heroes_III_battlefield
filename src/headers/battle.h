#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "hero.h"

typedef std::pair<int, int> cordsT;

class Battle
{
    Hero mEnemy;
    Hero mPlayer;
    const int mSize = 11;

    public:
        Battle(Hero player, Hero enemy);

        Hero getPlayer() {return mPlayer;}
        Hero getEnemy() {return mEnemy;}
        const int getSize() {return mSize;}

        void GenerateDefUnitsCords(Hero Hero, bool leftSide);

        bool MoveStack(cordsT startCords, cordsT finalCords, bool isPlayer);
        bool CheckBasicAttackPoss(cordsT itsCords, cordsT opponentCords, bool isPlayer);
        std::pair<bool, bool> PerformAttack(cordsT itsCords, cordsT opponentCords,
                                            bool isPlayer, int attackingStackType);

        std::vector<cordsT> GetAllOccupiedCords();
        std::vector<cordsT> GetPossibleMoveCords(cordsT cords, bool isPlayer); 
        std::pair<bool, cordsT> GetPossibleAttackCords(cordsT itsCords,
                                                     cordsT opponentCords,
                                                     bool isPlayer);
};