#include <vector>
#include <string>
#include <memory>
#include "ability.h"

typedef std::shared_ptr<Ability> APtr;

class Hero
{
    std::string mName;
    int mAttack;
    int mProtection;
    int mLevel;
    int mExp;
    std::vector<APtr> mAbilities; 

    public:
        Hero(std::string name,
            int attack,
            int protection,
            int level = 0,
            int exp = 0)
        {
            mName = name;
            mAttack = attack;
            mProtection = protection;
            mAbilities = std::vector<APtr>();
            mLevel = level;
            mExp = exp;
        }

        std::string getName() {return mName;}
        int getAttack() {return mAttack;}
        int getProtection() {return mProtection;}
        int getLevel() {return mLevel;}
        int getExp() {return mExp;}
        std::vector<APtr> getAbilities() {return mAbilities;}

        void setName(std::string sGname) {mName = sGname;}
        void setAttack(int nGatt) {mAttack = nGatt;}
        void setProtection(int nGprot) {mProtection = nGprot;}
        void setLevel(int nGlevel) {mLevel = nGlevel;}
        void setExp (int nGexp) {mExp = nGexp;}

        void AddExp (int nGexp) {mExp += nGexp;}
        void AddAttack(int nGatt) {mAttack += nGatt;}
        void AddProtection(int nGprot) {mProtection += nGprot;}
        void AddAbility(const Ability& Ab);
    

};