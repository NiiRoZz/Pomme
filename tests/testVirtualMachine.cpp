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
	compiler.addFile("std.pomme");\
	compiler.addString(s);\
	ObjFunction *function = compiler.compile(true);\
	EXPECT_TRUE(function != nullptr);\
	InterpretResult result = vm.interpret(function);\
	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);\
	defineStdNative(vm);\


void defineStdNative(VirtualMachine& vm)
{
	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operator+", "int"), [] (VirtualMachine& vm, int argCount, ObjPrimitive* primitive, Value* args) {
		assert(argCount == 1);
        assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive* rhs = AS_PRIMITIVE(args[0]);
		
		return OBJ_VAL(vm.newInt(std::get<int64_t>(primitive->value) + std::get<int64_t>(rhs->value)));
	}));

	EXPECT_TRUE(vm.linkMethodNative("float", vm.getFunctionName("operator+", "float"), [] (VirtualMachine& vm, int argCount, ObjPrimitive* primitive, Value* args) {
		assert(argCount == 1);
        assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive* rhs = AS_PRIMITIVE(args[0]);
		
		return OBJ_VAL(vm.newFloat(std::get<double>(primitive->value) + std::get<double>(rhs->value)));
	}));

	EXPECT_TRUE(vm.linkMethodNative("float", vm.getFunctionName("operator-", "float"), [] (VirtualMachine& vm, int argCount, ObjPrimitive* primitive, Value* args) {
		assert(argCount == 1);
        assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive* rhs = AS_PRIMITIVE(args[0]);
		
		return OBJ_VAL(vm.newFloat(std::get<double>(primitive->value) - std::get<double>(rhs->value)));
	}));
}

TEST(TEST_VM, BasicTest)
{
    TEST_VM_TEST("void f() { float a = 5.0 + 5.0; float b = 5.0; print(a + 20.0 + b); \n };\n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, GlobalFunctionTest)
{
	TEST_VM_TEST("void f() { print(50.0); };\n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ScopeTest)
{
	TEST_VM_TEST("void f(float b) { float c = 0.0; c = 1.0; c = 2.0; print(b); print(c); };};\n");
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f", "float"), {FLOAT_VAL(vm, 100.0)});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

/*
TEST(TEST_VM, IfTest)
{
	TEST_VM_TEST("void f(float b) { float c = 0.0; if (1 == 1) {float d = 0.0;}; print(b); };};\n");

	InterpretResult result = vm.interpret(function);

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f", "float"), {NUMBER_VAL(100.0)});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}
*/

TEST(TEST_VM, GlobalNativeTest)
{
	TEST_VM_TEST("native float t(int a, int b, int c, float d); void f() { print(t(10, 20, 30, 40.5)); };\n");

	vm.linkGlobalNative(vm.getFunctionName("t", "int", "int", "int", "float"), [] (VirtualMachine& vm, int argCount, Value* args) {
		std::cout << "From native argcount : " << argCount << std::endl; 

		for (int i = 0; i < argCount; ++i)
		{
			vm.printValue(args[i]);
			std::cout << std::endl;
		}
	
		return OBJ_VAL(vm.newFloat(500.5));
	});

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassTest)
{
	TEST_VM_TEST("class TestClass { int k = 0; int g = 5; public void t() {int f = 50; print(f);}; }; void f() { int a = 10; TestClass oui = new TestClass(); TestClass non = new TestClass(); oui.t(); a = 25; oui.g = 35; non.g = 700; print(a); print(oui.g); print(non.g); };\n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassMethodTest)
{
	TEST_VM_TEST("class StructClass { int x = 0; int h = 10; public int y(int a) {print(a);}; };  class TestClass { StructClass z = new StructClass(); public int g(int a) {print(a);}; }; void f() { TestClass oui = new TestClass(); oui.g(50); oui.z.y(25); oui.z.x = 5; print(oui.z); print(oui.z.h); print(oui.z.x);  };\n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassConstructorTest)
{
	TEST_VM_TEST("class TestClass { public void f() {print(600);}; TestClass(int a) {print(a);}; }; void f() { TestClass oui = new TestClass(10); };\n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, AttributeMethodTest)
{
	TEST_VM_TEST("class TestClass { int x; int y; void meth(){ x = 8; y = 10; }; }; void f() { TestClass oui = new TestClass(); oui.meth(); print(oui.x); print(oui.y); }; \n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ThisVariableTest)
{
	TEST_VM_TEST("class TestClass { int x; int y; void meth(){ this.x = 500; this.y = 100; }; }; void f() { TestClass oui = new TestClass(); oui.meth(); print(oui.x); print(oui.y); }; \n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassStaticMethodTest)
{
	TEST_VM_TEST("class TestClass { int x() {}; static int y(int a) {print(a);}; }; void f() { TestClass.y(10); };\n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassStaticVarTest)
{
	TEST_VM_TEST("class TestClass { int x = 0; static int y = 587; }; void f() { print(TestClass.y); };\n");

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassNativeMethodTest)
{
	TEST_VM_TEST("class Other { static int t = 5; }; class TestClass { int z = 10; int x = 0; static int y = 23; native void meth(int a); }; void f() { TestClass oui = new TestClass(); oui.meth(573); print(oui.x); print(Other.t); };\n");

	EXPECT_TRUE(vm.linkMethodNative("TestClass", vm.getFunctionName("meth", "int"), [] (VirtualMachine& vm, int argCount, ObjInstance* instance, Value* args) {
		EXPECT_TRUE(argCount == 1);

		Value* x = instance->getField("x");

		if (x != nullptr)
		{
			*x = args[0];
		}

		Value* y = instance->getStaticField("y");
		EXPECT_TRUE(y != nullptr);
		EXPECT_EQ(std::get<int64_t>(AS_PRIMITIVE(*y)->value), 23);

		*vm.getStaticField("Other", "t") = OBJ_VAL(vm.newInt(123));
		
		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassNativeMethodCallGlobalTest)
{
	TEST_VM_TEST("int g(int a) {return a + 10;}; class TestClass { native int meth(int a); }; void f() { TestClass oui = new TestClass(); print(oui.meth(573)); };\n");

	EXPECT_TRUE(vm.linkMethodNative("TestClass", vm.getFunctionName("meth", "int"), [] (VirtualMachine& vm, int argCount, ObjInstance* instance, Value* args) {
		EXPECT_TRUE(argCount == 1);

		std::optional<Value> val = vm.callGlobalFunction(vm.getFunctionName("g", "int"), {args[0]});

		EXPECT_TRUE(val.has_value());

		return *val;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassNativeMethodCallMethodTest)
{
	TEST_VM_TEST("class TestClass { native int meth(int a); void update(float t) {print(\"update :\"); print(t);}; }; void f() { TestClass oui = new TestClass(); oui.meth(650); };\n");

	EXPECT_TRUE(vm.linkMethodNative("TestClass", vm.getFunctionName("meth", "int"), [] (VirtualMachine& vm, int argCount, ObjInstance* instance, Value* args) {
		EXPECT_TRUE(argCount == 1);
		
		std::optional<Value> val = vm.callMethodFunction(instance, vm.getFunctionName("update", "float"), {args[0]});

		EXPECT_TRUE(val.has_value());

		return *val;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}


TEST(TEST_VM, ClassCallMethodFromCPPTest)
{
	TEST_VM_TEST("class TestClass { void update(float t) {print(\"update :\"); print(t);}; };\n");

	ObjInstance* instance = vm.newInstance("TestClass");

	EXPECT_TRUE(instance != nullptr);

	result = vm.interpretMethodFunction(instance, vm.getFunctionName("update", "float"), {OBJ_VAL(vm.newFloat(625.5))});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, ClassLinkMethodInstanceTest)
{
	TEST_VM_TEST("class TestClass { native void method(float a); void update(float t) {method(t);}; };\n");

	ObjInstance* instance = vm.newInstance("TestClass");
	EXPECT_TRUE(instance != nullptr);

	EXPECT_TRUE(instance->linkMethodNative(vm.getFunctionName("method", "float"), [] (VirtualMachine& vm, int argCount, ObjInstance* instance, Value* args) {
		EXPECT_TRUE(argCount == 1);

		std::cout << "parameter : ";
		vm.printValue(args[0]);
		std::cout << std::endl;
		EXPECT_EQ(std::get<double>(AS_PRIMITIVE(args[0])->value), 510.23);

		return NULL_VAL;
	}));

	result = vm.interpretMethodFunction(instance, vm.getFunctionName("update", "float"), {OBJ_VAL(vm.newFloat(510.23))});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

#undef TEST_VM_TEST