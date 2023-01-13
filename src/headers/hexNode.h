#include <memory>
#include <vector>
#include "stack.h"

class HexNode
{
    typedef std::shared_ptr<HexNode> HNPtr;
    // it has indexes from 0 (upper right) to 5 (upper left)
    std::vector<HNPtr> mOrdNeighs; // starting from right up corner, down
    std::shared_ptr<Stack> mStack;
    bool mStepable;
    const unsigned int mNeighNum = 6;

    public:
        HexNode()
        {
            for (unsigned int _ = 0; _ < mNeighNum; ++_)
            {
                mOrdNeighs.push_back(HNPtr());
            }
            mStack = std::shared_ptr<Stack>();
            mStepable = true;

        }

        HexNode(HexNode& node)
        {
            mOrdNeighs = node.mOrdNeighs;
            mStack = node.mStack;
            mStepable = node.CanStep();
        }

        ~HexNode()
        {
            //TODO
        }

        std::vector<HNPtr>& getNeighbours() { 
            return mOrdNeighs;
        }

        std::shared_ptr<Stack>& getStack() { return mStack; }
        void setStack(Stack& stack)
        {
            mStack = std::make_shared<Stack>(stack);
            mStepable = false;
        }
        void setStack(std::shared_ptr<Stack> stack)
        {
            mStack = stack;
            mStepable = false;   
        }
        void FreeStack() {mStack = nullptr;}

        bool stepable() {return mStepable; }
        void setStepable(bool value) {mStepable = value;}

        friend bool operator== (const HexNode& lhs, const HexNode& rhs);
        bool CheckIfNeigh(HexNode& node);
        HNPtr GetNeigh(int i);
        bool CanStep();
        bool MoveStack(int i);
        std::shared_ptr<Stack> RetrieveStack();

};

