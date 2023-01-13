#include <utility>
#include <string>
#include <random>
#include "randomGenerator.h"

typedef std::unique_ptr<RandomGenerator> GPtr;

class Unit
{
    std::string mName;
    int mAttack;
    int mProtection;
    std::pair<int, int> mDamage;
    float mHP;


    public:
        
        Unit()
        {
            mName = "";
            mHP = 0;
            mAttack = 0;
            mProtection = 0;
            mDamage = {0, 0};
        }

        Unit(std::string name,
             float hp, int attack, int prot,
             std::pair<int, int> damage = {})
        {
            mName = name;
            mHP = hp;
            mAttack = attack;
            mProtection = prot;
            mDamage = damage;
        }

        std::string getName() {return mName;}
        float getHP() {return mHP;}
        int getAttack() {return mAttack;}
        int getProtection() {return mProtection;}
        std::pair<int, int> getDamage() {return mDamage;}

        void setName(std::string sGname) {mName = sGname;}
        void setHP(float hp) {mHP = hp;}
        void setAttack(int att) {mAttack = att;}
        void setProtection(int prot) {mProtection = prot;}
        void setDamage(std::pair<int, int> damage) {mDamage = damage;}

        void AddHP(float hp) {mHP += hp;}
        void AddAttack(int att) {mAttack += att;}
        void AddProtection(int prot) {mProtection += prot;}
        void AddDamage(int dam) {mDamage.first += dam; mDamage.second += dam;}

        void GetInjured(float damage);
        int GenerateDamage();

};