#include "../src/unit.cpp"
#include <gtest/gtest.h>


TEST(AddDamageTest, BasicTest)
{
    Unit unit = Unit("name", 20, 6, 3, std::pair<int, int>(2, 6));
    unit.AddDamage(-2);
    std::pair<int, int> tempDamage = std::pair<int, int>(0, 4);
    ASSERT_EQ(unit.GetDamage(), tempDamage);
}

TEST(GenerateDamageTest, PositiveTest)
{
    Unit unit = Unit("name", 20, 6, 3, std::pair<int, int>(2, 6));
    int damage = unit.GenerateDamage();
    ASSERT_TRUE(2 <= damage);
    ASSERT_TRUE(6 >= damage);
}

TEST(GenerateDamageTest, NegativeTest)
{
    Unit unit = Unit("name", 20, 6, 3, std::pair<int, int>(-20, -7));
    int damage = unit.GenerateDamage();
    ASSERT_TRUE(-20 <= damage);
    ASSERT_TRUE(-7 >= damage);
}

TEST(GenerateDamageTest, BothSidesTest)
{
    Unit unit = Unit("name", 20, 6, 3, std::pair<int, int>(-20, 20));
    int damage = unit.GenerateDamage();
    ASSERT_TRUE(-20 <= damage);
    ASSERT_TRUE(20 >= damage);  
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}