#include <vector>
#include <memory>
#include <utility>
#include <cstdlib>

typedef std::pair<int, int> cordsT;
class Stack
{
    int mID;
    // 0 - usual, 1 - shooter, (2- flying)
    int mType;

    unsigned int mHP;
    unsigned int mUnitHP;

    int mSize;
    int mSpeed;

    int mProtection;
    int mAttack;
    cordsT mDamage;

    cordsT mCords;

    public:
        typedef std::shared_ptr<Stack> SPtr;
        Stack()
        {
            mID = 0;
            mSize = 1;
            mProtection = 1;
            mAttack = 1;
            mSpeed = 1;
            mCords = cordsT();
        }

        Stack(int id)
        {
            Stack();
            mID = id;
        }

        Stack(int id, int unitHP,
              int size = 1, int speed = 1,
              int prot = 1, int att = 1):
              mID(id), mUnitHP(unitHP), mSize(size), mProtection(prot),
              mAttack(att), mSpeed(speed)
        {
            mHP = mUnitHP * mSize;
            mCords = cordsT();
        }

        Stack(const Stack& stack)
        {
            mID = stack.mID;
            mSize = stack.mSize;
            mProtection = stack.mProtection;
            mAttack = stack.mAttack;
        }

        ~Stack(){}

        int getID() {return mID;}
        int getPlayerType() {return mType;}
        int getSize() {return mSize;}
        int getSpeed() {return mSpeed;}
        int getProtection() {return mProtection;}
        int getAttack() {return mAttack;}
        cordsT getDamage() {return mDamage;}
        cordsT getCords() {return mCords;}

        void setID(int id) {mID = id;}
        void setPlayerType(int type) {mType = type;}
        void setSize(int size) {mSize = size;}
        void setSpeed(int speed) {mSpeed = speed;}
        void setProtection(int prot) {mProtection = prot;}
        void setAttack(int attack) {mAttack = attack;}
        void setDamage(cordsT damage) {mDamage = damage;}
        void setCords(cordsT cords) {mCords = cords;}

        bool BeAttacked(float damage);
        bool Attack(SPtr stackPtr);
        void AddUnits(SPtr stackPtr);

        int GenerateStackDamage();
        friend bool operator== (const Stack& lhs, const Stack& rhs);
};
