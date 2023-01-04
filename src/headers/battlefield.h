#include <vector>
#include "hexNode.h"

typedef std::vector<std::vector<HexNode>> MapNodes; 

class Battlefield
{
    MapNodes mMap;
    const unsigned int mSize = 13;

    public:
        Battlefield()
        {
            mMap = MapNodes();
            for (int i1 = 0; i1 < mSize; ++i1)
            {
                std::vector<HexNode> row = std::vector<HexNode>();
                for (int i2 = 0; i2 < mSize; ++i2)
                {
                    row.push_back(HexNode());
                }
                mMap.push_back(row);
            }
        }

        MapNodes& getMap() { return mMap;}

        HexNode& GetNode(int x, int y)
        {
            return mMap[x][y];
        }

        std::shared_ptr<Stack> GetStackPtr(int x, int y)
        {
            return mMap[x][y].getStack();
        }

        void InsertStack(int x, int y, Stack& stack)
        {
            mMap[x][y].setStack(stack);
        }
};