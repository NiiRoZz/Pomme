#include "gtest/gtest.h"
#include "Automate/Automaton.h"

using namespace Pomme;

TEST(TEST_AUTOMATE, Empty) {
    Automaton fa;

    EXPECT_EQ(fa.countStates(), 0u);
    EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(TEST_AUTOMATE, addState)
{
    Automaton fa;

    EXPECT_EQ(fa.addState(0),true);
    EXPECT_EQ(fa.addState(-1),false);
}

TEST(TEST_AUTOMATE, removeState)
{
    Automaton fa;

    fa.addState(0);
    EXPECT_EQ(fa.removeState(0),true);
    EXPECT_EQ(fa.removeState(0),false);
}

TEST(TEST_AUTOMATE, hasState)
{
    Automaton fa;

    fa.addState(0);
    EXPECT_EQ(fa.hasState(0),true);
    EXPECT_EQ(fa.hasState(10),false); // NOT IN IT
}

TEST(TEST_AUTOMATE, isStateInitial)
{
    Automaton fa;

    fa.addState(1);
    EXPECT_EQ(fa.isStateInitial(1),false);

    fa.setStateInitial(1);
    EXPECT_EQ(fa.isStateInitial(1),true);

    fa.addState(0);
    EXPECT_EQ(fa.isStateInitial(0),false);
}

TEST(TEST_AUTOMATE, isStateFinal)
{
    Automaton fa;

    fa.addState(1);
    EXPECT_EQ(fa.isStateFinal(1),false);

    fa.setStateFinal(1);
    EXPECT_EQ(fa.isStateFinal(1),true);

    fa.addState(0);
    EXPECT_EQ(fa.isStateFinal(0),false);
}

TEST(TEST_AUTOMATE, addTransition)
{
    Automaton fa;

    fa.addState(0);
    fa.addState(1);

    EXPECT_EQ(fa.addTransition(0,1),true);
    EXPECT_EQ(fa.addTransition(0,2),false); // NO STATE 2 DEFINED
}

TEST(TEST_AUTOMATE, removeTransition)
{
    Automaton fa;

    fa.addState(0);
    EXPECT_EQ(fa.hasState(0),true);

    fa.addState(1);
    EXPECT_EQ(fa.hasState(1),true);


    fa.addTransition(0,1);
    EXPECT_EQ(fa.hasTransition(0,1),true);

    fa.removeTransition(0,1);
    EXPECT_EQ(fa.hasTransition(0,1),false);
}

TEST(TEST_AUTOMATE, hasTransition)
{
    Automaton fa;

    fa.addState(0);
    fa.addState(1);
    fa.addState(2);

    EXPECT_EQ(fa.addTransition(0,1),true);
    EXPECT_EQ(fa.addTransition(0,2),true);

    EXPECT_EQ(fa.hasTransition(0,1),true);
    EXPECT_EQ(fa.hasTransition(0,2),true);
    EXPECT_EQ(fa.hasTransition(12,0),false);
}

TEST(TEST_AUTOMATE, countStates)
{
    Automaton fa;

    for(int i=0; i <3 ;i++){
        fa.addState(i);
        EXPECT_EQ(fa.hasState(i),true);
    }
    EXPECT_EQ(fa.countStates(),3);

    EXPECT_EQ(fa.removeState(0),true);
    EXPECT_EQ(fa.countStates(),2);

    EXPECT_EQ(fa.removeState(1),true);
    EXPECT_EQ(fa.countStates(),1);

    EXPECT_EQ(fa.removeState(2),true);
    EXPECT_EQ(fa.countStates(),0);
}

TEST(TEST_AUTOMATE, countTransitions)
{
    Automaton fa;

    EXPECT_EQ(fa.countTransitions(),0);

    fa.addState(0);
    fa.addState(1);
    fa.addState(2);
    fa.addState(3);

    fa.addTransition(0,1);
    fa.addTransition(1,2);
    fa.addTransition(2,3);

    EXPECT_EQ(fa.countTransitions(),3);


    std::cout << fa << std::endl;
    fa.removeTransition(2,3);
    std::cout << fa << std::endl;

    EXPECT_EQ(fa.countTransitions(),2);
}
