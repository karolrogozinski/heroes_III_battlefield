#include "../src/character.cpp"
#include <gtest/gtest.h>

TEST(AttackTest, BasicTest)
{
    CCharacter* cObj1 = new CCharacter();
    cObj1->SetHP(10);
    cObj1->SetProtection(2);

    CCharacter* cObj2 = new CCharacter();
    cObj2->SetAttack(5);

    cObj2->Attack(cObj1);

    ASSERT_EQ(7, cObj1->GetHP()); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}