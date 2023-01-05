#include "./headers/hexNode.h"

typedef std::shared_ptr<HexNode> HNPtr;

bool operator== (const HexNode& lhs, const HexNode& rhs)
{
    return lhs.mOrdNeighs == rhs.mOrdNeighs &&
        lhs.mStack.get() == rhs.mStack.get();
}

bool HexNode::CheckIfNeigh(HexNode& node)
{
    HexNode* tempPNode = new HexNode(node);
    bool rValue = this == tempPNode;
    delete tempPNode;
    return rValue;
}

HNPtr HexNode::GetNeigh(int i)
{
    return mOrdNeighs[i];
}

bool HexNode::CanStep()
{
    return mStack->getID() == -1 ? false : true;
}

bool HexNode::MoveStack(int i)
{
    HNPtr neigh = GetNeigh(i);
    if (!neigh->stepable())
    {
        return false;
    }

    std::shared_ptr<Stack> tmpP = neigh->getStack();
    neigh->FreeStack();
    this->mStack = tmpP;

    this->mStepable = false;
    neigh->setStepable(true);

    return true;
}

std::shared_ptr<Stack> HexNode::RetrieveStack()
{
    if (mStack == nullptr || mStepable)
    {   
        mStack = nullptr;
        mStepable = true;
        return nullptr;
    }

    std::shared_ptr<Stack> tempPtr = mStack;
    mStack = nullptr;
    mStepable = true;

    return tempPtr;
}
