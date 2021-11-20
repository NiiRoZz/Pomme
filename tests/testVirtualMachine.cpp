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
	VirtualMachine vm;\
    Compiler compiler(vm);\
	compiler.addString(s);\
	ObjFunction *function = compiler.compile(true);\
	EXPECT_TRUE(function != nullptr);\

TEST(TEST_VM, BasicTest)
{
    TEST_VM_TEST("void f() { float a = 5.0 + 5.0; float b = 5.0; print(a + 20.0 + b); print(\"Hello world, My name is Lucas\"); if (1 == 1) {print(10.0);}; if (0 == 1) {print(20.0);}; float d = 50.0; \n };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, GlobalFunctionTest)
{
	TEST_VM_TEST("void f() { print(50.0); };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ScopeTest)
{
	TEST_VM_TEST("void f(float b) { float c = 0.0; c = 1.0; c = 2.0; print(b); print(c); };};\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f", "float"), {NUMBER_VAL(100.0)});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, IfTest)
{
	TEST_VM_TEST("void f(float b) { float c = 0.0; if (1 == 1) {float d = 0.0;}; print(b); };};\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f", "float"), {NUMBER_VAL(100.0)});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, GlobalNativeTest)
{
	TEST_VM_TEST("native float t(int a, int b, int c, float d); void f() { print(t(10, 20, 30, 40.5)); };\n");

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
	TEST_VM_TEST("class TestClass { int k = 0; int g = 5; public void t() {int f = 50; print(f);}; }; void f() { int a = 10; TestClass oui = new TestClass(); TestClass non = new TestClass(); oui.t(); a = 25; oui.g = 35; non.g = 700; print(a); print(oui.g); print(non.g); };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassMethodTest)
{
	TEST_VM_TEST("class StructClass { int x = 0; int h = 10; public int y(int a) {print(a);}; };  class TestClass { StructClass z = new StructClass(); public int g(int a) {print(a);}; }; void f() { TestClass oui = new TestClass(); oui.g(50); oui.z.y(25); oui.z.x = 5; print(oui.z); print(oui.z.h);  };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassConstructorTest)
{
	TEST_VM_TEST("class TestClass { public void f() {print(600);}; TestClass(int a) {print(a);}; }; void f() { TestClass oui = new TestClass(10); print(oui); };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, AttributeMethodTest)
{
	TEST_VM_TEST("class TestClass { int x; int y; void meth(){ x = 8; y = 10; }; }; void f() { TestClass oui = new TestClass(); oui.meth(); print(oui.x); print(oui.y); }; \n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ThisVariableTest)
{
	TEST_VM_TEST("class TestClass { int x; int y; void meth(){ this.x = 500; this.y = 100; }; }; void f() { TestClass oui = new TestClass(); oui.meth(); print(oui.x); print(oui.y); }; \n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassStaticMethodTest)
{
	TEST_VM_TEST("class TestClass { int x() {}; static int y(int a) {print(a);}; }; void f() { TestClass.y(10); };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassStaticVarTest)
{
	TEST_VM_TEST("class TestClass { int x = 0; static int y = 587; }; void f() { print(TestClass.y); };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassNativeMethodTest)
{
	TEST_VM_TEST("class Other { static int t = 5; }; class TestClass { int z = 10; int x = 0; static int y = 23; native void meth(int a); }; void f() { TestClass oui = new TestClass(); oui.meth(573); print(oui.x); print(Other.t); };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	EXPECT_TRUE(vm.linkMethodNative("TestClass", vm.getFunctionName("meth", "int"), [&vm] (int argCount, ObjInstance* instance, Value* args) {
		std::cout << "From native method argcount : " << argCount << std::endl; 

		if (argCount  == 1)
		{
			Value* x = instance->getField("x");

			if (x != nullptr)
			{
				*x = args[0];
			}

			Value* y = instance->getStaticField("y");
			EXPECT_EQ(AS_NUMBER(*y), 23);

			*vm.getStaticField("Other", "t") = NUMBER_VAL(123);
		}
		
		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassNativeMethodCallGlobalTest)
{
	TEST_VM_TEST("int g(int a) {return a + 10;}; class TestClass { native int meth(int a); }; void f() { TestClass oui = new TestClass(); print(oui.meth(573)); };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	EXPECT_TRUE(vm.linkMethodNative("TestClass", vm.getFunctionName("meth", "int"), [&vm] (int argCount, ObjInstance* instance, Value* args) {
		if (argCount  == 1)
		{
			std::optional<Value> val = vm.callGlobalFunction(vm.getFunctionName("g", "int"), {args[0]});

			EXPECT_TRUE(val.has_value());

			return *val;
		}
		
		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassNativeMethodCallMethodTest)
{
	TEST_VM_TEST("class TestClass { native int meth(int a); void update(float t) {print(\"update :\"); print(t);}; }; void f() { TestClass oui = new TestClass(); oui.meth(650); };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	EXPECT_TRUE(vm.linkMethodNative("TestClass", vm.getFunctionName("meth", "int"), [&vm] (int argCount, ObjInstance* instance, Value* args) {
		if (argCount  == 1)
		{
			std::optional<Value> val = vm.callMethodFunction(instance, vm.getFunctionName("update", "float"), {args[0]});

			EXPECT_TRUE(val.has_value());

			return *val;
		}
		
		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassCallMethodFromCPPTest)
{
	TEST_VM_TEST("class TestClass { void update(float t) {print(\"update :\"); print(t);}; };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	ObjInstance* instance = vm.newInstance("TestClass");

	EXPECT_TRUE(instance != nullptr);

	result = vm.interpretMethodFunction(instance, vm.getFunctionName("update", "float"), {NUMBER_VAL(520)});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassLinkMethodInstanceTest)
{
	TEST_VM_TEST("class TestClass { native void method(int a); void update(int t) {method(t);}; };\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);

	ObjInstance* instance = vm.newInstance("TestClass");
	EXPECT_TRUE(instance != nullptr);

	EXPECT_TRUE(instance->linkMethodNative(vm.getFunctionName("method", "int"), [&vm] (int argCount, ObjInstance* instance, Value* args) {
		if (argCount  == 1)
		{
			std::cout << "Hello value : " << AS_NUMBER(args[0]) << std::endl;
		}

		return NULL_VAL;
	}));

	result = vm.interpretMethodFunction(instance, vm.getFunctionName("update", "int"), {NUMBER_VAL(520)});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

#undef TEST_VM_TEST