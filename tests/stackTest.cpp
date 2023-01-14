#include "../src/headers/stack.h"
#include <gtest/gtest.h>

TEST(StupidTest, BasicTest)
{
    ASSERT_TRUE(true);
}

TEST(ConstructorTest, DefaultConstructor)
{
    Stack stack = Stack();
    ASSERT_EQ(0, stack.getUnits().size());
    ASSERT_EQ(0, stack.getCords().first);
}   

TEST(ConcatStackTest, NewUnit)
{
    Stack stack = Stack(2137);
    std::vector<UPtr> units;
    Unit* u1 = new Unit("u1", 21.37, 5, 2, {2, 7});
    Unit* u2 = new Unit("u2", 73.12, 6, 3, {3, 8});
    Unit* u3 = new Unit("u3", 32.48, 7, 4, {4, 9});
    Stack stack2 = Stack();
    stack2.AddUnit(u1);
    stack2.AddUnit(u2);
    stack2.AddUnit(u3);

    stack.ConcatStack(std::make_shared<Stack>(stack2));
    ASSERT_EQ(3, stack.getUnits().size());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}