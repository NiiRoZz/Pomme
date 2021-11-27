#include "gtest/gtest.h"

#include <iostream>
#include "Automate/Automaton.h"
#include "PommeLexer.h"
#include "PommeLexerTokenManager.h"
#include "AutomateVisitor.h"
#include "MyErrorHandler.h"

using namespace Pomme;

#define TEST_AUTOMATE_TEST(testString) \
	std::string s = testString;\
	CharStream charStream(s.c_str(), s.size() - 1, 1, 1);\
	MyErrorHandler *myErrorHandler = new MyErrorHandler();\
	PommeLexerTokenManager scanner(&charStream);\
	PommeLexer lexer(&scanner);\
	lexer.setErrorHandler(myErrorHandler);\
	PommeNode* tree = static_cast<PommeNode*>(lexer.input());\
	EXPECT_EQ(myErrorHandler->getErrorCount(), 0);\
	std::stringstream buffer;\
	std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());\
	tree->dump("");\
	std::string text = buffer.str();\
	std::cout.rdbuf(old);\

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

TEST(TEST_AUTOMATE, Graph_Basic) {
    TEST_AUTOMATE_TEST("class test{}; class test2{}; class test3 extends test{}; \n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);

    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    ASTpommeClass* n = dynamic_cast<ASTpommeClass*>(visitor.dependanceGraph.getState(0)->node);
    std::string ident = dynamic_cast<ASTident*>(n->jjtGetChild(0))->m_Identifier;

    ASTpommeClass* n2 = dynamic_cast<ASTpommeClass*>(visitor.dependanceGraph.getState(1)->node);
    std::string ident2 = dynamic_cast<ASTident*>(n2->jjtGetChild(0))->m_Identifier;

    EXPECT_EQ(ident,"test");
    EXPECT_EQ(ident2, "test2");

    EXPECT_EQ(visitor.dependanceGraph.getState(0)->modded ,false);
    EXPECT_EQ(visitor.dependanceGraph.getState(0)->extend ,false);
    EXPECT_EQ(visitor.dependanceGraph.getState(1)->modded ,false);
    EXPECT_EQ(visitor.dependanceGraph.getState(1)->extend ,false);

    EXPECT_EQ(visitor.dependanceGraph.getState(2)->modded ,false);
    EXPECT_EQ(visitor.dependanceGraph.getState(2)->extend ,true);
}

TEST(TEST_AUTOMATE, Graph_Attribute) {
    TEST_AUTOMATE_TEST("class test2{}; class test{ int x; test2 y; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,0));
}

TEST(TEST_AUTOMATE, Graph_SelfLoop) {
    TEST_AUTOMATE_TEST("class test{ test y; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,0));
}
TEST(TEST_AUTOMATE, Graph_3Loop) {
    TEST_AUTOMATE_TEST("class test{ test1 y; }; class test1{ test2 y; }; class test2{ test y; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,3);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,1));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,2));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(2,0));
}

TEST(TEST_AUTOMATE, Graph_DefinedAfter) {
    TEST_AUTOMATE_TEST("class test{ test2 y; }; class test2{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,1));
}

TEST(TEST_AUTOMATE, Graph_ExtendsAfter) {
    TEST_AUTOMATE_TEST("class test extends test2 {}; class test2{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,1));
}

TEST(TEST_AUTOMATE, Graph_Extends) {
    TEST_AUTOMATE_TEST("class test2{}; class test extends test2 {};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,0));
}

TEST(TEST_AUTOMATE, Graph_Complex) {
    TEST_AUTOMATE_TEST("class test5{}; " // 0
                       "class test2{ test3 y; }; " // 1
                       "class test extends test2 {}; " // 2
                       "class test3 extends test5{ test2 x;};\n"); // 3
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,4);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(3,0));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,3));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(2,1));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(3,1));
}
