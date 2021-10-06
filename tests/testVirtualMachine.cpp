#include "gtest/gtest.h"

#include "PommeLexer.h"
#include "Compiler.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"
#include "PommeLexerTokenManager.h"
#include "MyErrorHandler.h"

using namespace Pomme;

#define TEST_VM_TEST(testString) \
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

TEST(TEST_VM, BasicTest)
{
    TEST_VM_TEST("void f() { float a = 5.0 + 5.0; float b = 5.0; print(a + 20.0 + b); print(\"Hello world, My name is Lucas\"); \n if (1 == 1) {print(\"if!!\");\n}; if (0 == 1) {print(\"if 2!!\");\n} else {print(\"else!!\");\n}; print(\"finish\");\n };\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    Compiler compiler(vm);

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	result = vm.interpretGlobalFunction("f");
}

TEST(TEST_VM, GlobalFunctionTest)
{
	TEST_VM_TEST("void f() { print(50.0); };\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    Compiler compiler(vm);

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	result = vm.interpretGlobalFunction("f");
}

#undef TEST_VM_TEST