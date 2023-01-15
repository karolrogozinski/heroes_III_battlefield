#include "../src/include/stack.cpp"
#include <gtest/gtest.h>

TEST(StupidTest, BasicTest)
{
    ASSERT_TRUE(true);
}

TEST(ConstructorTest, BiggestConstructor)
{
    Stack stack = Stack(1, 2, 10, 3, 4, 5, 6);
    ASSERT_EQ(1, stack.getID());
    ASSERT_EQ(2, stack.getType());
    ASSERT_EQ(30, stack.getHP());
    ASSERT_EQ(10, stack.getUnitHP());
    ASSERT_EQ(3, stack.getSize());
    ASSERT_EQ(4, stack.getSpeed());
    ASSERT_EQ(5, stack.getProtection());
    ASSERT_EQ(6, stack.getAttack());
    ASSERT_TRUE(0 == stack.getCords().first && 0 == stack.getCords().second);
    ASSERT_TRUE(0 == stack.getDamage().first && 0 == stack.getDamage().second);
}

TEST(BeAttackedTest, NotDead)
{
    Stack stack = Stack(1, 2, 10, 3, 4, 5, 6);
    bool result = stack.BeAttacked(21.37);
    ASSERT_EQ(1, stack.getSize());
    ASSERT_EQ(8, stack.getHP());
    ASSERT_FALSE(result);
}

TEST(BeAttackedTest, Dead)
{
    Stack stack = Stack(1, 2, 10, 3, 4, 5, 6);
    bool result = stack.BeAttacked(3849);
    ASSERT_EQ(0, stack.getSize());
    ASSERT_EQ(0, stack.getHP());
    ASSERT_TRUE(result);
}

TEST(AttackTest, NotDead)
{
    Stack stack1 = Stack(1, 2, 10, 3, 4, 5, 6);
    stack1.setDamage({2, 4});
    Stack stack2 = Stack(2, 3, 10, 4, 5, 5, 7);
    bool result = stack1.Attack(stack2);
    ASSERT_FALSE(result);
    ASSERT_TRUE(stack2.getHP()>=27 && stack2.getHP()<= 33);
    ASSERT_TRUE(stack2.getSize() >= 3 && stack2.getSize() <= 4);
}

TEST(AttackTest, Dead)
{
    Stack stack1 = Stack(1, 2, 10, 3, 4, 5, 6);
    stack1.setDamage({2, 4});
    Stack stack2 = Stack(2, 3, 10, 2, 5, 5, 7);
    bool result = stack1.Attack(stack2);
    // ASSERT_TRUE(result);
    ASSERT_EQ(0, stack2.getHP());
    // ASSERT_EQ(0, stack2.getSize());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}