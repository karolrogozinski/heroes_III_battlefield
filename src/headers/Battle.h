#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Hero.h"

typedef std::pair<int, int> IntPair;

class Battle
{
    Hero player_;
    Hero enemy_;
    const int size_ = 11;

    public:
        Battle(Hero player, Hero enemy);

        Hero getPlayer() {return player_;}
        Hero getEnemy() {return enemy_;}
        const int getSize() {return size_;}

        void setPlayer(Hero player) {player_ = player;}
        void setEnemy(Hero enemy) {enemy_ = enemy;}

        void generateDefUnitsCords(Hero Hero, bool leftSide);

        bool moveStack(IntPair startCords, IntPair finalCords, bool isPlayer);
        bool checkBasicAttackPoss(IntPair itsCords, IntPair opponentCords, bool isPlayer);
        std::vector<bool> performAttack(IntPair itsCords, IntPair opponentCords,
                                            bool isPlayer);

        std::vector<IntPair> getAllOccupiedCords();
        bool checkMovePossibility(IntPair itsCords, IntPair finalCords, bool isPlayer);
        std::vector<IntPair> getPossibleMoveCords(IntPair cords, bool isPlayer); 
        std::pair<bool, IntPair> getPossibleAttackCords(IntPair itsCords,
                                                     IntPair opponentCords,
                                                     bool isPlayer);
};