#include "hero.h"
// zloto 0, drewno 1, kamien 2, exp 3
class Pickup
{
    unsigned int mID;
    unsigned int mValue;
    bool mStepable = true;
    bool mUsed = false;

    public:
        Pickup() : mID(0), mValue(0) {};
        Pickup(unsigned int id, unsigned int value)
        {
            mID = id;
            mValue = value;
        }

        unsigned int getID() {return mID;}
        unsigned int getValue() {return mValue;}

        void setID(unsigned int id) {mID = id;}
        void setValue(unsigned int value) {mValue = value;}

        void Use(Hero& hero);
};
