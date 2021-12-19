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
    ASTPommeClass* n = dynamic_cast<ASTPommeClass*>(visitor.dependanceGraph.getState(0)->node);
    std::string ident = dynamic_cast<ASTPommeIdent*>(n->jjtGetChild(0))->m_Identifier;

    ASTPommeClass* n2 = dynamic_cast<ASTPommeClass*>(visitor.dependanceGraph.getState(1)->node);
    std::string ident2 = dynamic_cast<ASTPommeIdent*>(n2->jjtGetChild(0))->m_Identifier;

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
    TEST_AUTOMATE_TEST("class test2{}; class test{ int x; static test2 y; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,1));
}

TEST(TEST_AUTOMATE, Graph_SelfLoop) {
    TEST_AUTOMATE_TEST("class test{ static test y; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,0));
}
TEST(TEST_AUTOMATE, Graph_3Loop) {
    TEST_AUTOMATE_TEST("class test{ static test1 y; }; class test1{ static test2 y; }; class test2{ static test y; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,3);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,0));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(2,1));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,2));
}

TEST(TEST_AUTOMATE, Graph_DefinedAfter) {
    TEST_AUTOMATE_TEST("class test{ static test2 y; }; class test2{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,0));
}

TEST(TEST_AUTOMATE, Graph_ExtendsAfter) {
    TEST_AUTOMATE_TEST("class test extends test2 {}; class test2{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,0));
}

TEST(TEST_AUTOMATE, Graph_Extends) {
    TEST_AUTOMATE_TEST("class test2{}; class test extends test2 {};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,1));
}

TEST(TEST_AUTOMATE, Graph_Complex) {
    TEST_AUTOMATE_TEST("class test5{}; " // 0
                       "class test2{ static test3 y; }; " // 1
                       "class test extends test2 {}; " // 2
                       "class test3 extends test5{ static test2 x;};\n"); // 3
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions() ,4);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,3));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(3,1));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,2));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,3));
}

TEST(TEST_AUTOMATE, Graph_Multiple) {
    TEST_AUTOMATE_TEST("class test2{}; class test3{}; class test{ static test2 x; static test3 y; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,2));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,2));
}

TEST(TEST_AUTOMATE, Graph_MultipleAfter) {
    TEST_AUTOMATE_TEST("class test{ static test2 x; static test3 y; }; class test2{}; class test3{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,0));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(2,0));

    for(auto it : visitor.classToBeResolved)
    {
        std::cout << it.first << " = ";
        for(auto ut : it.second)
        {
            std::cout << ut << " ";
        }
        std::cout << std::endl;
    }
}

TEST(TEST_AUTOMATE, Graph_Loop1) {
    TEST_AUTOMATE_TEST("class test2{}; class test extends test2 {};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.hasLoop(), false);
}

TEST(TEST_AUTOMATE, Graph_Loop2) {
    TEST_AUTOMATE_TEST("class test{ static test2 x; static test3 y; }; class test2{}; class test3{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    EXPECT_EQ(visitor.dependanceGraph.hasLoop(), false);
}

TEST(TEST_AUTOMATE, Graph_Loop3) {
    TEST_AUTOMATE_TEST("class test{ static test2 x;}; class test2{ static test x;};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    EXPECT_EQ(visitor.dependanceGraph.hasLoop(), true);
}

TEST(TEST_AUTOMATE, Graph_Loop4) {
    TEST_AUTOMATE_TEST("class test{ static test2 x;}; class test2{ static test3 x;}; class test3{ static test x;};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    EXPECT_EQ(visitor.dependanceGraph.hasLoop(), true);
}

TEST(TEST_AUTOMATE, Graph_Loop5) {

    Automaton dependanceGraph;
    dependanceGraph.addState(0);
    dependanceGraph.addState(1);
    dependanceGraph.addState(2);

    dependanceGraph.addTransition(0,1);
    dependanceGraph.addTransition(0,2);
    dependanceGraph.addTransition(1,2);
    dependanceGraph.addTransition(2,0);

    EXPECT_EQ(dependanceGraph.hasLoop(), true);
}

TEST(TEST_AUTOMATE, Graph_Loop6) {

    Automaton dependanceGraph;
    dependanceGraph.addState(0);
    dependanceGraph.addState(1);
    dependanceGraph.addState(2);
    dependanceGraph.addState(3);
    dependanceGraph.addState(4);

    dependanceGraph.addTransition(0,1);
    dependanceGraph.addTransition(1,2);
    dependanceGraph.addTransition(2,3);
    dependanceGraph.addTransition(3,4);
    dependanceGraph.addTransition(4,0);

    EXPECT_EQ(dependanceGraph.hasLoop(), true);
}


TEST(TEST_AUTOMATE, Graph_Sort) {

    TEST_AUTOMATE_TEST("class test{ static test2 x; static test3 y; }; class test2{}; class test3{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    auto it = visitor.dependanceGraph.topologicalSort();

    int expect[] = {2, 1, 0};
    int expect2[] = {1, 2, 0};

    EXPECT_EQ(it.size(), 3);
    for (int i = 0; i < it.size(); ++i)
    {
        std::cout << it.at(i) << std::endl;
        EXPECT_TRUE( (it.at(i) == expect[i] || it.at(i) == expect2[i]));
    }
}

TEST(TEST_AUTOMATE, Graph_Sort2) {

    TEST_AUTOMATE_TEST("class test{ static test2 x; }; class test2{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;


    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    auto it = visitor.dependanceGraph.topologicalSort();
    int expect[] = {1,0};
    EXPECT_EQ(it.size(), 2);
    for (int i = 0; i < it.size(); ++i)
    {
        EXPECT_EQ(it.at(i), expect[i]) << "Vectors x and y differ at index " << i;
    }

}
TEST(TEST_AUTOMATE, Graph_Sort3) {

    TEST_AUTOMATE_TEST("class test5{}; " // 0
                       "class test2{}; " // 1
                       "class test extends test3 {}; " // 2
                       "class test3 extends test5{ static test2 x;};\n"); // 3
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;


    EXPECT_EQ(visitor.dependanceGraph.countStates(), 4);
    auto it = visitor.dependanceGraph.topologicalSort();
    int expect[] = {0,1,3,2};
    EXPECT_EQ(it.size(), 4);
    for (int i = 0; i < it.size(); ++i)
    {
        EXPECT_EQ(it.at(i), expect[i]) << "Vectors x and y differ at index " << i;
    }
}

TEST(TEST_AUTOMATE, Graph_Sort4) {

    Automaton automate;

    automate.addState(0);
    automate.addState(1);
    automate.addState(2);
    automate.addState(3);
    automate.addState(4);
    automate.addState(5);
    automate.addState(6);
    automate.addState(7);

    automate.addTransition(0,3);
    automate.addTransition(1,3);
    automate.addTransition(1,4);

    automate.addTransition(2,4);
    automate.addTransition(2,7);

    automate.addTransition(3,5);
    automate.addTransition(3,6);
    automate.addTransition(3,7);

    automate.addTransition(4,6);

    std::cout << automate<< std::endl;

    auto it = automate.topologicalSort();
    int expect[] = {0,1,2,3,4,5,7,6}; // not deterministic
    //  {0,1,2,3,4,5,6,7}; possible too

    for(auto ot : it)
    {
        std::cout << ot << std::endl;
    }
    EXPECT_EQ(it.size(), 8);
    for (int i = 0; i < it.size(); ++i)
    {
        EXPECT_EQ(it.at(i), expect[i]) << "Vectors x and y differ at index " << i;
    }
}

TEST(TEST_AUTOMATE, Graph_Sort5) {

    Automaton automate;

    // https://medium.com/@bolerio/scheduling-tasks-and-drawing-graphs-the-coffman-graham-algorithm-3c85eb975ab
    automate.addState(0);
    automate.addState(1);
    automate.addState(2);
    automate.addState(3);
    automate.addState(4);
    automate.addState(5);
    automate.addState(6);
    automate.addState(7);
    automate.addState(8);
    automate.addState(9);
    automate.addState(10);
    automate.addState(11);
    automate.addState(12);

    automate.addTransition(0,3);
    automate.addTransition(1,3);
    automate.addTransition(1,4);
    automate.addTransition(2,4);
    automate.addTransition(2,5);
    automate.addTransition(3,6);
    automate.addTransition(3,7);
    automate.addTransition(4,8);
    automate.addTransition(5,8);
    automate.addTransition(5,9);
    automate.addTransition(9,12);
    automate.addTransition(8,12);
    automate.addTransition(8,7);
    automate.addTransition(6,10);
    automate.addTransition(7,10);
    automate.addTransition(7,11);
    
    std::cout << automate<< std::endl;

    auto it = automate.topologicalSort();
    for(auto ot : it)
    {
        std::cout << ot << std::endl;
    }
    EXPECT_EQ(it.size(), 13);
}


TEST(TEST_AUTOMATE, Graph_Enum) {
    TEST_AUTOMATE_TEST("enum test{}; enum test1{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 0);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
}

TEST(TEST_AUTOMATE, Graph_Enum2) {
    TEST_AUTOMATE_TEST("enum test{}; enum test1 extends test{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,1));
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
}

TEST(TEST_AUTOMATE, Graph_Enum3) {
    TEST_AUTOMATE_TEST("enum test extends test3{}; enum test1 extends test{};  enum test3{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(2,0));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,1));
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
}
TEST(TEST_AUTOMATE, Graph_ClassEnum) {
    TEST_AUTOMATE_TEST("enum test{}; class depend{ static test x;};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,1));
}

TEST(TEST_AUTOMATE, Graph_ClassEnum2) {
    TEST_AUTOMATE_TEST("enum test extends test2{}; enum test2{}; class depend{ static test x;};  class depend2 extends depend{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;
    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 3);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 4);
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(1,0));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(0,2));
    EXPECT_TRUE(visitor.dependanceGraph.hasTransition(2,3));
}

TEST(TEST_AUTOMATE, Graph_LoopEnum) {
    TEST_AUTOMATE_TEST("enum test extends test2{}; enum test2 extends test{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.hasLoop(), true);
}


TEST(TEST_AUTOMATE, Graph_EnumClass) {
    TEST_AUTOMATE_TEST("enum testEnum{ a }; class test{ static testEnum x; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
}

TEST(TEST_AUTOMATE, Graph_EnumExtendsClass) {
    TEST_AUTOMATE_TEST("enum testEnum extends testEnum2{ a }; class test{ static testEnum x; }; enum testEnum2{ a };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(2,0), true);
}


TEST(TEST_AUTOMATE, Graph_Assignement) {
    TEST_AUTOMATE_TEST("class test{ static int x = 8; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 0);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 1);
}

TEST(TEST_AUTOMATE, Graph_GlobalReturnTypeIsClass) {
    TEST_AUTOMATE_TEST(" class c2{}; c1 test2(int x, int k){};  class c1 extends c2{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(2,1), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,2), true);
}

TEST(TEST_AUTOMATE, Graph_GlobalParamTypeIsClass) {
    TEST_AUTOMATE_TEST("c1 test2(c2 x, int k){};  class c2{}; class c1{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(2,0), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}

TEST(TEST_AUTOMATE, Graph_GlobalParamTypeIsClassVoidReturn) {
    TEST_AUTOMATE_TEST("void test2(c2 x, int k){};  class c2{}; \n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}

TEST(TEST_AUTOMATE, Graph_GlobalOverloadDependanceParam) {
    TEST_AUTOMATE_TEST("void test2(c2 x){};  void test2(c1 x){}; class c2{}; class c1{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 4);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(2,0), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(3,1), true);
}

TEST(TEST_AUTOMATE, Graph_DoubleDependance) {
    TEST_AUTOMATE_TEST("class c2{}; class c1{ static c2 x; static c2 y;};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
}


TEST(TEST_AUTOMATE, Graph_AssignementVarDependanceToResolve)
{
    TEST_AUTOMATE_TEST("class test2{ static int j = test.k(); static int k = test.a; }; class test{ static int a = 8; static int k(){}; };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}

TEST(TEST_AUTOMATE, Graph_AssignementVarDependance)
{
    TEST_AUTOMATE_TEST("class test{ static int k(){}; }; class test2{ static int j = test.k(); };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
}

TEST(TEST_AUTOMATE, Graph_AssignementGlobalDependance)
{
    TEST_AUTOMATE_TEST("class test2{ static int j = func(8); }; int func(int w){};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}

TEST(TEST_AUTOMATE, Graph_AssignementGlobalExp)
{
    TEST_AUTOMATE_TEST("class test2{ static int j = func(8 + 3); }; int func(int w){};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}

TEST(TEST_AUTOMATE, Graph_AssignementGlobalMultipleExp)
{
    TEST_AUTOMATE_TEST("class test2{ static int j = func((8+3), (1-2), (6*4), (9/9)); }; int func(int w, int x, int z, int om){};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}

TEST(TEST_AUTOMATE, Graph_AssignementGlobalMultipleExpBool)
{
    TEST_AUTOMATE_TEST("class test2{ static int j = func((8 > 3), (1>=2), (6<=4), (9<9)); }; int func(bool w, bool x, bool z, bool om){};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}

TEST(TEST_AUTOMATE, Graph_AssignementGlobalMultipleExpBool2)
{
    TEST_AUTOMATE_TEST("class test2{ static int j = func((8 == 3), (1!=2)); }; int func(bool w, bool x){};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 1);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 2);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}

TEST(TEST_AUTOMATE, Graph_AssignementGlobalWithOtherDependance)
{
    TEST_AUTOMATE_TEST("class test{}; class test2{ static test f; static int j = func2(f); }; int func2(test k){};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 3);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,2), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(2,1), true);
}

TEST(TEST_AUTOMATE, Graph_AssignementGlobalWithNestedFund)
{
    TEST_AUTOMATE_TEST("class test2{ static int j = func(func2()); }; int func2(){}; int func(bool w, bool x){};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(2,0), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,0), true);
}


TEST(TEST_AUTOMATE, Graph_GlobalDependanceOverloading)
{
    TEST_AUTOMATE_TEST("int func(int j){}; int func(int j, int k){}; class test{ static int z = func(7); static int k = func(8,7); };\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,2), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,2), true);
}

TEST(TEST_AUTOMATE, Graph_Modded)
{
    TEST_AUTOMATE_TEST("class test2{}; modded class test2{}; modded class test2{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,2), true);
}

TEST(TEST_AUTOMATE, Graph_ModdedExtend)
{
    TEST_AUTOMATE_TEST("class test2{}; modded class test2{};  class test3 extends test2{}; modded class test2{};\n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 3);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 4);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,2), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,3), true);
}

TEST(TEST_AUTOMATE, Graph_ModdedBeforeDeclaration)
{
    TEST_AUTOMATE_TEST("modded class test2{}; modded class test2{}; class test2{}; \n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,2), true);
}

TEST(TEST_AUTOMATE, Graph_ModdedMiddleDefinition)
{
    TEST_AUTOMATE_TEST("modded class test2{}; class test2{}; modded class test2{}; \n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 2);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 3);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,2), true);
}

TEST(TEST_AUTOMATE, Graph_ModdedChain)
{
    TEST_AUTOMATE_TEST("class test2{}; modded class test2{}; modded class test2{}; modded class test2{}; modded class test2{}; modded class test2{}; \n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 5);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 6);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(0,1), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(1,2), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(2,3), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(3,4), true);
    EXPECT_EQ(visitor.dependanceGraph.hasTransition(4,5), true);
}


TEST(TEST_AUTOMATE, Graph_Static)
{
    TEST_AUTOMATE_TEST("class test2{ static int k = 8; }; \n");
    std::cout << text << std::endl;

    AutomateVisitor visitor;
    tree->jjtAccept(&visitor, nullptr);
    std::cout << visitor.dependanceGraph << std::endl;

    EXPECT_EQ(visitor.dependanceGraph.countTransitions(), 0);
    EXPECT_EQ(visitor.dependanceGraph.countStates(), 1);
}




