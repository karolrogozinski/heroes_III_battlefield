#include "../src/headers/stack.h"
#include <gtest/gtest.h>

TEST(StupidTest, BasicTest)
{
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}