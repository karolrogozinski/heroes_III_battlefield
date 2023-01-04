#include <memory>
#include <vector>
#include "stack.h"

typedef std::shared_ptr<HexNode> HNPtr;

class HexNode
{
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

        std::shared_ptr<Stack> getStack() { return mStack; }
        void setStack(Stack& stack)
        {
            mStack = std::make_shared<Stack>(stack);
        }

        friend bool operator== (const HexNode& lhs, const HexNode& rhs);
        bool CheckIfNeigh(HexNode& node);
        HNPtr GetNeigh(int i);
        bool CanStep();

};