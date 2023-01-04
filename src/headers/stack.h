#include "unit.h"
#include <vector>
#include <memory>

typedef std::shared_ptr<Unit> UPtr;

class Stack
{
    std::vector<UPtr> mUnits;
    int mSize;
    int mProtection;
    int mAttack;

    public:
        Stack()
        {
            mUnits = {};
            mSize = 0;
            mProtection = 0;
            mAttack = 0;
        }

        std::vector<UPtr> getUnits() {return mUnits;}
        int getSize() {return mSize;}
        int getProtection() {return mProtection;}
        int getAttack() {return mAttack;}

        void AddUnit();
        void AddUnit(UPtr unit);
        void AddUnit(Unit* unit);

        void BeAttacked(float damage);
        void Attack(Stack& stack);
};
