#include "./headers/hexNode.h"

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