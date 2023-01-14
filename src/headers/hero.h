#include <vector>
#include <string>
#include <memory>
#include <math.h>
#include "stack.h"

typedef std::shared_ptr<Stack> SPtr;

class Hero
{
    std::string mName;
    bool mIsPlayer;
    std::vector<SPtr> mForces;
    const int mForcesNum = 7;
    // int mLevel;
    // int mExp;
    // int mLvlExpLimit;
    // std::pair<int, int> mCords;

    public:
        Hero() : mName(""), mIsPlayer(false){}

        Hero(std::string name, bool isPlayer) : mName(name), mIsPlayer(isPlayer) {}

        Hero(std::string name, bool isPlayer, std::vector<SPtr> forces) :
             mName(name), mIsPlayer(isPlayer), mForces(forces) {}

        std::string getName() {return mName;}
        bool getIsPlayer() {return mIsPlayer;}
        std::vector<SPtr>& getForces() {return mForces;}

        void setName(std::string sGname) {mName = sGname;}
        void setIsPlayer(bool isPlayer) {mIsPlayer = isPlayer;}
        void setForces(std::vector<SPtr> forces) {mForces = forces;}

        SPtr GetStack(std::pair<int, int> cords);
        void AddStack(SPtr stackPtr);

};