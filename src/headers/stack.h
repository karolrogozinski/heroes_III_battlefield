#include "unit.h"
#include <vector>
#include <memory>

typedef std::shared_ptr<Unit> UPtr;

class Stack
{
    int mID;
    std::vector<UPtr> mUnits;
    int mSize;
    int mProtection;
    int mAttack;

    public:
        Stack()
        {
            mID = 0;
            mUnits = {};
            mSize = 0;
            mProtection = 0;
            mAttack = 0;
        }

        Stack(int id)
        {
            Stack();
            mID = id;
        }

        Stack(const Stack& stack)
        {
            mID = stack.mID;
            mUnits = stack.mUnits;
            mSize = stack.mSize;
            mProtection = stack.mProtection;
            mAttack = stack.mAttack;
        }

        ~Stack()
        {
            //TODO
        }

        std::vector<UPtr> getUnits() {return mUnits;}
        int getSize() {return mSize;}
        int getProtection() {return mProtection;}
        int getAttack() {return mAttack;}
        int getID() {return mID;}

        void AddUnit();
        void AddUnit(UPtr unit);
        void AddUnit(Unit* unit);

        void BeAttacked(float damage);
        void Attack(Stack& stack);

        friend bool operator== (const Stack& lhs, const Stack& rhs);
};
