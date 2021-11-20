#include "gtest/gtest.h"

#include "PommeLexer.h"
#include "TypeChecker.h"
#include "PommeLexerTokenManager.h"
#include "MyErrorHandler.h"

#include <iostream>

using namespace Pomme;

#define TEST_TYPECHECKER_TEST(testString) \
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
	//std::cout << text << std::endl;

TEST(TEST_TYPECHECKER, ClassComplete)
{
    TEST_TYPECHECKER_TEST("class test { int a = 8;  boolean b = 8; void meth(){ int b = 7; }; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, FileComplete)
{
    TEST_TYPECHECKER_TEST("void meth(){};  void xd(int j){}; class test { int a = 8;  boolean b = 8; void meth(int abc){ boolean b = 7; }; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, Class)
{
    TEST_TYPECHECKER_TEST("class A { int a = 1;}; class B { int a = 1;}; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassAttributeRedefinition)
{
    TEST_TYPECHECKER_TEST("class test { int a; int a;}; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassRedefinition)
{
    TEST_TYPECHECKER_TEST("class test {}; class test {};\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, GlobalFunction)
{
    TEST_TYPECHECKER_TEST(" void meth(int k){ int a; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassMethodRedefinition)
{
    TEST_TYPECHECKER_TEST("class test { void meth(){}; void meth(){}; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, GlobalFunctionRedefinition)
{
    TEST_TYPECHECKER_TEST("void meth(){}; void meth(){};\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, CompleteClass)
{
    TEST_TYPECHECKER_TEST("class test { int a; void meth(int n){}; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, GlobalFunctionOverloading)
{
    TEST_TYPECHECKER_TEST(" int meth(int n){}; int meth(){};\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ParametersRedefinitionWithDifferentType)
{
    TEST_TYPECHECKER_TEST(" int meth(int n, bool n){};\n");
    std::cout << text << std::endl;
    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);
    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, FunctionRedefinitionWithDifferentType)
{
    TEST_TYPECHECKER_TEST(" int meth(int n){}; void meth(int n){};\n");
    std::cout << text << std::endl;
    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);
    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, TestIndex)
{
    TEST_TYPECHECKER_TEST("class Test{ int a = 8; int j = 7; int meth(int n){}; int j(){}; };\n");
    std::cout << text << std::endl;
    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);
    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, Constant)
{
    TEST_TYPECHECKER_TEST("class test { const int k = 10;  const int v = 8;}; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, StaticMethod)
{
    TEST_TYPECHECKER_TEST("class test { static int test(){}; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test")->second.functions.find("test!")->second.keywords.count("static"));
}

TEST(TEST_TYPECHECKER, VisibilityMethod)
{
    TEST_TYPECHECKER_TEST("class test { public int testPublic(){}; private int testPrivate(){}; protected int testProtected(){}; int testPrivate2(){}; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test")->second.functions.find("testPublic!")->second.keywords.count("public"));
    EXPECT_TRUE(visitor.classMap.find("test")->second.functions.find("testPrivate!")->second.keywords.count("private"));
    EXPECT_TRUE(visitor.classMap.find("test")->second.functions.find("testPrivate2!")->second.keywords.count("private"));
    EXPECT_TRUE(visitor.classMap.find("test")->second.functions.find("testProtected!")->second.keywords.count("protected"));

}
TEST(TEST_TYPECHECKER, OverrideMethod)
{
    TEST_TYPECHECKER_TEST("class test { override int f(){}; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test")->second.functions.find("f!")->second.keywords.count("override"));
}
TEST(TEST_TYPECHECKER, StaticVisibilityMethod)
{
    TEST_TYPECHECKER_TEST("class test { static public int test(){}; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;

    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }

    EXPECT_TRUE(visitor.classMap.find("test")->second.functions.find("test!")->second.keywords.count("static"));
    EXPECT_TRUE(visitor.classMap.find("test")->second.functions.find("test!")->second.keywords.count("public"));
}
TEST(TEST_TYPECHECKER, ExtendedClass) {
    TEST_TYPECHECKER_TEST("class test { int t; void t2(){}; }; class test2 extends test {}; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test2")->second.keywords.count("extends"));
    EXPECT_TRUE(visitor.classMap.find("test2")->second.functions.count("t2!"));
}
TEST(TEST_TYPECHECKER, ExtendingNonExistingClass) {
    TEST_TYPECHECKER_TEST("class test extends t2{}; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

    //todo check exception here
}
TEST(TEST_TYPECHECKER, OverridingWithoutExtends) {
    TEST_TYPECHECKER_TEST("class test{ override void x(){}; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, OverridingWithoutDefinitionInParent) {
    TEST_TYPECHECKER_TEST("class test {  void a(){}; }; class test2 extends test{ override void b() {}; }; \n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, RedefinitionOfVarFromParentClass) {
    TEST_TYPECHECKER_TEST("class test{ int a; }; class test2 extends test { bool a;  bool b; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

    EXPECT_TRUE(visitor.classMap.find("test")->second.attributes.count("test::a"));
    EXPECT_TRUE(visitor.classMap.find("test2")->second.attributes.count("test::a"));
    EXPECT_TRUE(visitor.classMap.find("test2")->second.attributes.find("test::a")->second.variableType == "int");
    EXPECT_TRUE(visitor.classMap.find("test2")->second.attributes.count("test2::b"));
}
TEST(TEST_TYPECHECKER, AccessToNonExistingMethod) {
    TEST_TYPECHECKER_TEST("class test{ void x(){ op(10); }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, AccessToExistingMethod) {
    TEST_TYPECHECKER_TEST("class test{ void k(){}; void op(int x){}; void x(){ op(10); }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, CallingGlobalFunctionNotDefined) {
    TEST_TYPECHECKER_TEST("void x(){ op(10); };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, CallingFunctionOnInstanceReturn) {
    TEST_TYPECHECKER_TEST("x op(){}; class x{ void t(){}; void meth(){ op().t(); }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, CallingFunctionOnInstanceReturnNotExisting) {
    TEST_TYPECHECKER_TEST("x op(){}; class x{ void meth(){ op().t(); }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, MultipleAccessProperty) {
    TEST_TYPECHECKER_TEST("x op(){}; class x{ x t(){}; void meth(){ op().t().t(); }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, MultipleAccessP) {
    TEST_TYPECHECKER_TEST("x op(){}; class x{ x t(){}; void meth(){ op().t().t().t(); };};\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, LocalsDefinition) {
    TEST_TYPECHECKER_TEST("class x{ void meth(){ int a; int b; }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, NotDefinedVariableInFunction) {
    TEST_TYPECHECKER_TEST("class x{ void meth(){ k = 8; }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, DefinedVariableInLocals) {
    TEST_TYPECHECKER_TEST("class x{ void meth(){ int x; x = 8; }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, DefinedVariableInAttribute) {
    TEST_TYPECHECKER_TEST("class x{ int x; int y; void meth(){ x = 8; y = 10; }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, DefinedVariableInHeader) {
    TEST_TYPECHECKER_TEST("class x{ void meth(int x){ x = 8; }; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, RedefinedVariableInHeader) {
    TEST_TYPECHECKER_TEST("class x{ void meth(int y, int y){}; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, MethodNameSameAsClass) {
    TEST_TYPECHECKER_TEST("class x { void x(int x, int y) {}; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, Constructor) {
    TEST_TYPECHECKER_TEST("class x { x(int x, int y) {}; x() {}; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ConstructorNotCorrectName) {
    TEST_TYPECHECKER_TEST("class x { z(int x, int y) {}; x() {}; };\n");

    std::cout << text << std::endl;

    TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}


