#include <vector>
#include <string>
#include <memory>
#include <math.h>
#include "stack.h"

class Hero
{
    std::string mName;
    bool mIsPlayer;
    std::vector<Stack> mForces;
    int mForcesNum = 7;

    public:
        Hero() : mName(""), mIsPlayer(false){}

        Hero(std::string name, bool isPlayer) : mName(name), mIsPlayer(isPlayer) {}

        std::string getName() {return mName;}
        bool getIsPlayer() {return mIsPlayer;}
        std::vector<Stack>& getForces() {return mForces;}

        void setName(std::string sGname) {mName = sGname;}
        void setIsPlayer(bool isPlayer) {mIsPlayer = isPlayer;}
        void setForces(std::vector<Stack> forces) {mForces = forces;}

        Stack GetStack(std::pair<int, int> cords);
        void AddStack(Stack& stack);

};