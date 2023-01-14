#include <vector>
#include <memory>
#include <utility>

#include "unit.h"

typedef std::shared_ptr<Unit> UPtr;

class Stack
{
    int mID;
    int mPlayerType;
    std::vector<UPtr> mUnits;
    int mSize;
    int mProtection;
    int mAttack;
    int mSpeed;
    std::pair<int, int> mCords;

    public:
        typedef std::shared_ptr<Stack> SPtr;
        Stack()
        {
            mID = 0;
            mUnits = {};
            mSize = 0;
            mProtection = 0;
            mAttack = 0;
            mSpeed = 2;
            mCords = std::pair<int, int>();
        }

        Stack(int id)
        {
            Stack();
            mID = id;
        }

        Stack(int id, int size, int prot, int att, int speed):
            mID(id), mSize(size), mProtection(prot), mAttack(att), mSpeed(speed)
        {
            mUnits = {};
            mCords = std::pair<int, int>();
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

        std::vector<UPtr>& getUnits() {return mUnits;}
        int getSize() {return mSize;}
        int getProtection() {return mProtection;}
        int getAttack() {return mAttack;}
        int getID() {return mID;}
        int getSpeed() {return mSpeed;}
        std::pair<int, int> getCords() {return mCords;}

        void setCords(std::pair<int, int> cords) {mCords = cords;}
        void setID(int id) {mID = id;}
        void setSize(int size) {mSize = size;}
        void setProtection(int prot) {mProtection = prot;}

        // void AddUnit();
        void AddUnit(UPtr unit);
        // void AddUnit(Unit* unit);
        void ConcatStack(SPtr stackPtr);

        void BeAttacked(float damage);
        // bool Attack(Stack& stack);
        bool Attack(std::shared_ptr<Stack> stackPtr);

        friend bool operator== (const Stack& lhs, const Stack& rhs);
};
