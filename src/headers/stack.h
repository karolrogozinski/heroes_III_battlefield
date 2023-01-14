#include <vector>
#include <memory>
#include <utility>
#include <cstdlib>

class Stack
{
    int mID;
    int mPlayerType;

    unsigned int mHP;
    unsigned int mUnitHP;

    int mSize;
    int mSpeed;

    int mProtection;
    int mAttack;
    std::pair<int, int> mDamage;

    std::pair<int, int> mCords;

    public:
        typedef std::shared_ptr<Stack> SPtr;
        Stack()
        {
            mID = 0;
            mSize = 1;
            mProtection = 1;
            mAttack = 1;
            mSpeed = 1;
            mCords = std::pair<int, int>();
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
            mCords = std::pair<int, int>();
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
        int getPlayerType() {return mPlayerType;}
        int getSize() {return mSize;}
        int getSpeed() {return mSpeed;}
        int getProtection() {return mProtection;}
        int getAttack() {return mAttack;}
        std::pair<int, int> getDamage() {return mDamage;}
        std::pair<int, int> getCords() {return mCords;}

        void setID(int id) {mID = id;}
        void setPlayerType(int type) {mPlayerType = type;}
        void setSize(int size) {mSize = size;}
        void setSpeed(int speed) {mSpeed = speed;}
        void setProtection(int prot) {mProtection = prot;}
        void setAttack(int attack) {mAttack = attack;}
        void setDamage(std::pair<int, int> damage) {mDamage = damage;}
        void setCords(std::pair<int, int> cords) {mCords = cords;}

        bool BeAttacked(float damage);
        bool Attack(SPtr stackPtr);

        int GenerateStackDamage();
        friend bool operator== (const Stack& lhs, const Stack& rhs);
};
