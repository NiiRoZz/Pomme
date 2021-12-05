#include "gtest/gtest.h"


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    //::testing::GTEST_FLAG(filter) = "TEST_LEXER_PARSER.*";
    //::testing::GTEST_FLAG(filter) = "TEST_VM.*";
    //::testing::GTEST_FLAG(filter) = "TEST_TYPECHECKER.*";
    //::testing::GTEST_FLAG(filter) = "TEST_VM.bench*";
    //::testing::GTEST_FLAG(filter) = "TEST_AUTOMATE.*";
    //::testing::GTEST_FLAG(filter) = "TEST_AUTOMATE.Graph*";

    return RUN_ALL_TESTS();
}
