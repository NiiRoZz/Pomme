#include "gtest/gtest.h"

#include "PommeLexer.h"
#include "TypeChecker.h"
#include "VM/VirtualMachine.h"
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

    VirtualMachine vm;
    TypeChecker typeChecker(vm);
    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 0);
}

TEST(TEST_TYPECHECKER, Class)
{
    TEST_TYPECHECKER_TEST("class A { int a = 1;}; class B { int a = 1;}; \n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    TypeChecker typeChecker(vm);
    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 0);
}

TEST(TEST_TYPECHECKER, ClassAttributeRedefinition)
{
    TEST_TYPECHECKER_TEST("class test { int a; int a;}; \n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    TypeChecker typeChecker(vm);
    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 1);
}

TEST(TEST_TYPECHECKER, ClassRedefinition)
{
    TEST_TYPECHECKER_TEST("class test {}; class test {};\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    TypeChecker typeChecker(vm);
    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 1);
}

TEST(TEST_TYPECHECKER, GlobalFunction)
{
    TEST_TYPECHECKER_TEST(" void meth(int k){ int a; }; \n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    TypeChecker typeChecker(vm);

    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 0);
}

TEST(TEST_TYPECHECKER, ClassMethodRedefinition)
{
    TEST_TYPECHECKER_TEST("class test { void meth(){}; void meth(){}; }; \n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    TypeChecker typeChecker(vm);

    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 1);
}

TEST(TEST_TYPECHECKER, GlobalFunctionRedefinition)
{
    TEST_TYPECHECKER_TEST("void meth(){}; void meth(){};\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    TypeChecker typeChecker(vm);

    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 1);
}

TEST(TEST_TYPECHECKER, CompleteClass)
{
    TEST_TYPECHECKER_TEST("class test { int a; void meth(int n){}; }; \n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    TypeChecker typeChecker(vm);

    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 0);
    for(const auto& error : errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, GlobalFunctionOverloading)
{
    TEST_TYPECHECKER_TEST(" void meth(int n){}; void meth(){};\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    TypeChecker typeChecker(vm);

    std::vector<std::string> errors = typeChecker.typeCheck(tree);

    EXPECT_EQ(errors.size(), 0);
    for(const auto& error : errors ){
        std::cout << error << std::endl;
    }
    // todo store full signature of function instead of just name
}