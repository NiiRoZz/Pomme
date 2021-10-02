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
    TEST_VM_TEST("void f() { print(5.0 + 10.0); };\n");

    std::cout << text << std::endl;

	ObjString functionName;
    ObjFunction function;
    function.obj.type = ObjType::OBJ_FUNCTION;
    function.arity = 0;
    function.name = &functionName;

    VirtualMachine vm;
    Compiler compiler(tree, vm, function);

	InterpretResult result = vm.interpret(&function);
}

#undef TEST_VM_TEST