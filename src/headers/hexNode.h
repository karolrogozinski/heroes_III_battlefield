#include <memory>
#include <vector>
#include "stack.h"

typedef std::shared_ptr<HexNode> HNPtr;

class HexNode
{
    std::vector<HNPtr> mOrdNeighs; // starting from right up corner, down
    std::shared_ptr<Stack> mStack;
    const unsigned int mSize = 6;

    public:
        HexNode()
        {
            for (unsigned int _ = 0; _ < mSize; ++_)
            {
                mOrdNeighs.push_back(HNPtr());
            }
        }

        HexNode(HexNode& node)
        {
            mOrdNeighs = node.mOrdNeighs;
            mStack = node.mStack;
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

};