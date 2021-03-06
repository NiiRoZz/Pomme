#include "gtest/gtest.h"

#include "PommeLexer.h"
#include "Compiler.h"
#include "VirtualMachine.h"
#include "PommeLexerTokenManager.h"
#include "MyErrorHandler.h"

#include <iostream>
#include <fstream>

using namespace Pomme;

#define TEST_COMPILER_TEST(testString) \
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

TEST(TEST_COMPILER, BasicTest)
{
	TEST_COMPILER_TEST("class test { void test(){ int64_t a = 2; float b = 5.25123; string c = \"Hello World!\"; }; };\n");

    std::cout << text << std::endl;

    VirtualMachine virtualMachine;
    Compiler compiler(tree, virtualMachine);
}