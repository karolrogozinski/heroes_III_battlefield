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

        void generateDefUnitsCords(Hero hero, bool left_side);

        bool moveStack(IntPair start_cords, IntPair final_cords, bool is_player);
        bool checkBasicAttackPoss(IntPair its_cords, IntPair opponent_cords, bool is_player);
        std::vector<bool> performAttack(IntPair its_cords, IntPair opponent_cords,
                                            bool is_player);

        std::vector<IntPair> getAllOccupiedCords();
        bool checkMovePossibility(IntPair its_cords, IntPair final_cords, bool is_player);
        std::vector<IntPair> getPossibleMoveCords(IntPair cords, bool is_player); 
        std::pair<bool, IntPair> getPossibleAttackCords(IntPair its_cords,
                                                     IntPair opponent_cords,
                                                     bool is_player);
        std::vector<bool> contrattack(bool, std::pair<bool, IntPair>, IntPair, IntPair, int);
};