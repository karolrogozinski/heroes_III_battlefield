#include <vector>
#include <string>
#include <memory>
#include <math.h>
#include "ability.h"
#include "stack.h"

typedef std::shared_ptr<Ability> APtr;
typedef std::shared_ptr<Stack> SPtr;

class Hero
{
    std::string mName;
    bool mPlayer;
    int mAttack;
    int mProtection;
    int mLevel;
    int mExp;
    int mLvlExpLimit;
    std::vector<unsigned int> mGoods;
    std::vector<APtr> mAbilities;
    std::vector<SPtr> mForces;
    std::pair<int, int> mCords;
    const int mForcesNum = 7;

    public:
        Hero() : mPlayer(false), mName(""), mAttack(0), mProtection(0),
                 mLevel(0), mExp(0), mLvlExpLimit(25)
            {
                mAbilities = std::vector<APtr>();
                mForces = std::vector<SPtr>();
                mGoods = std::vector<unsigned int>();
                for (unsigned int _ = 0; _ < 4; ++_)
                {
                    mGoods.push_back(0);
                }
                mCords = {0, 0};
            }

        Hero(std::string name,
            bool type,
            int attack,
            int protection,
            int level = 0,
            int exp = 0,
            int firstExpLimit = 25)
        {
            mName = name;
            mPlayer = type;
            mAttack = attack;
            mProtection = protection;
            mAbilities = std::vector<APtr>();
            mForces = std::vector<SPtr>();
            mGoods = std::vector<unsigned int>();
            for (unsigned int _ = 0; _ < 4; ++_)
            {
                mGoods.push_back(0);
            }
            mLevel = level;
            mExp = exp;
            mLvlExpLimit = firstExpLimit;
        }

        std::string getName() {return mName;}
        int getAttack() {return mAttack;}
        int getProtection() {return mProtection;}
        int getLevel() {return mLevel;}
        int getExp() {return mExp;}
        std::vector<APtr>& getAbilities() {return mAbilities;}
        std::vector<SPtr>& getForces() {return mForces;}
        SPtr getStack(std::pair<int, int> cords);

        void setName(std::string sGname) {mName = sGname;}
        void setAttack(int nGatt) {mAttack = nGatt;}
        void setProtection(int nGprot) {mProtection = nGprot;}
        void setLevel(int nGlevel) {mLevel = nGlevel;}
        void setExp (int nGexp) {mExp = nGexp;}
        void setCords (int x, int y) {mCords.first = x; mCords.second = y;}

        void AddExp (int nGexp) {mExp += nGexp;}
        void AddAttack(int nGatt) {mAttack += nGatt;}
        void AddProtection(int nGprot) {mProtection += nGprot;}
        void AddAbility(const Ability& Ab);
        void AddForce(Stack& stack);
        void AddGood(unsigned int i, unsigned int value);
        void ReduceGood(unsigned int i, unsigned int value);

        int CountNewExpLimit();
        void AddStack(SPtr stackPtr);

};