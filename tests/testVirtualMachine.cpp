#include "gtest/gtest.h"

#include "PommeLexer.h"
#include "Compiler.h"
#include "TypeChecker.h"
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
    TEST_VM_TEST("void f() { float a = 5.0 + 5.0; float b = 5.0; print(a + 20.0 + b); print(\"Hello world, My name is Lucas\"); if (1 == 1) {print(10.0);}; if (0 == 1) {print(20.0);}; float d = 50.0; \n };\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    Compiler compiler(vm);

	TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
	for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, GlobalFunctionTest)
{
	TEST_VM_TEST("void f() { print(50.0); };\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    Compiler compiler(vm);

	TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
	for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ScopeTest)
{
	TEST_VM_TEST("void f(float b) { float c = 0.0; c = 1.0; c = 2.0; print(b); print(c); };};\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    Compiler compiler(vm);

	TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
	for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f", "float"), {NUMBER_VAL(100.0)});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, IfTest)
{
	TEST_VM_TEST("void f(float b) { float c = 0.0; if (1 == 1) {float d = 0.0;}; print(b); };};\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    Compiler compiler(vm);

	TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
	for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f", "float"), {NUMBER_VAL(100.0)});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, GlobalNativeTest)
{
	TEST_VM_TEST("native float t(int a, int b, int c, float d); void f() { print(t(10, 20, 30, 40.5)); };\n");

    std::cout << text << std::endl;

    VirtualMachine vm;
    Compiler compiler(vm);

	TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    //EXPECT_EQ(visitor.errors.size(), 0);
	for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	vm.linkGlobalNative(vm.getFunctionName("t", "int", "int", "int", "float"), [](int argCount, Value* args) {
		std::cout << "From native argcount : " << argCount << std::endl; 

		for (int i = 0; i < argCount; ++i)
		{
			std::cout << "AS_NUMBER arg " << i << " : " << AS_NUMBER(args[i]) << std::endl;
		}
	
		return NUMBER_VAL(500.0);
	});

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassTest)
{
	TEST_VM_TEST("class TestClass { int g = 5; public void t() {int f = 50; print(f);}; }; void f() { int a = 10; TestClass oui = new TestClass(); TestClass non = new TestClass(); oui.t(); a = 25; oui.g = 35; non.g = 700; print(a); print(oui.g); print(non.g); };\n");

    std::cout << text << std::endl;

	VirtualMachine vm;
    Compiler compiler(vm);

	TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
	for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassMethodTest)
{
	TEST_VM_TEST("class StructClass { int h = 10; public int g(int a) {print(a);}; };  class TestClass { StructClass h = new StructClass(); public int g(int a) {print(a);}; }; void f() { TestClass oui = new TestClass(); oui.g(50); oui.h.g(25); print(oui.h); print(oui.h.h);  };\n");

    std::cout << text << std::endl;

	VirtualMachine vm;
    Compiler compiler(vm);

	TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
	for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassConstructorTest)
{
	TEST_VM_TEST("class TestClass { public void f() {print(600);}; public void TestClass(int a) {print(a);}; }; void f() { TestClass oui = new TestClass(10); print(oui); };\n");

    std::cout << text << std::endl;

	VirtualMachine vm;
    Compiler compiler(vm);

	TypeChecker typeChecker;
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);

    EXPECT_EQ(visitor.errors.size(), 0);
	for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }

	ObjFunction *function = compiler.compile(tree);

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

#undef TEST_VM_TEST