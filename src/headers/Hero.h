#include <vector>
#include <string>
#include <memory>
#include <math.h>
#include "Stack.h"

class Hero
{
    std::string name_;
    bool isPlayer_;
    std::vector<Stack> forces_;
    int forcesNum_ = 7;

    public:
        Hero() : name_(""), isPlayer_(false){}

        Hero(std::string name, bool isPlayer) : name_(name), isPlayer_(isPlayer) {}

        Hero(std::string name, bool isPlayer, std::vector<Stack> forces) :
             name_(name), isPlayer_(isPlayer), forces_(forces) {}

        std::string getName() {return name_;}
        bool getIsPlayer() {return isPlayer_;}
        std::vector<Stack> getForces() {return forces_;}

        void setName(std::string sGname) {name_ = sGname;}
        void setIsPlayer(bool isPlayer) {isPlayer_ = isPlayer;}
        void setForces(std::vector<Stack> forces) {forces_ = forces;}

        Stack& getStack(std::pair<int, int> cords);
        void addStack(Stack stack);

};