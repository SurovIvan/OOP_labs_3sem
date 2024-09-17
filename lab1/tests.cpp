#include "gtest/gtest.h"
#include "lab.h"
#include <string>

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(couting_vowels("LOLOLO")==3);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(couting_vowels("LGDsgsgg")==0);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(couting_vowels("HeLlO WoRlD")==3);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(couting_vowels("I love C++")==3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}