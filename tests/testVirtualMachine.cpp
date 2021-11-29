#include "gtest/gtest.h"

#include "PommeLexer.h"
#include "Compiler.h"
#include "TypeChecker.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"
#include "PommeLexerTokenManager.h"
#include "MyErrorHandler.h"

#include <benchmark/benchmark.h>

using namespace Pomme;

#define TEST_VM_TEST(testString) \
	std::string s = testString;\
	VirtualMachine vm;\
    Compiler compiler(vm);\
	compiler.addFile(std::string(POMME_BIN_PATH) + "std.pomme");\
	compiler.addString(s);\
	ObjFunction *function = compiler.compile(true);\
	EXPECT_TRUE(function != nullptr);\
	vm.started = true;\
	InterpretResult result = vm.interpret(function);\
	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);\
	defineStdNative(vm);\


void defineStdNative(VirtualMachine& vm)
{
	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operator+", "int"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 1);
        assert(primitive->primitiveType == PrimitiveType::INT);
		assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(primitive);
		ObjPrimitive<int64_t>* rhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
		
		return PrimitiveVal(vm.newInt(lhs->value + rhs->value));
	}));

	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operator-", "int"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 1);
        assert(primitive->primitiveType == PrimitiveType::INT);
		assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(primitive);
		ObjPrimitive<int64_t>* rhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
		
		return PrimitiveVal(vm.newInt(lhs->value - rhs->value));
	}));

	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operator<", "int"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 1);
        assert(primitive->primitiveType == PrimitiveType::INT);
		assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(primitive);
		ObjPrimitive<int64_t>* rhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
		
		return PrimitiveVal(vm.newBool(lhs->value < rhs->value));
	}));

	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operator-"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 0);
        assert(primitive->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(primitive);
		
		return PrimitiveVal(vm.newInt(-(lhs->value)));
	}));

	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operator+", "float"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 1);
        assert(primitive->primitiveType == PrimitiveType::INT);
		assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(primitive);
		ObjPrimitive<double>* rhs = static_cast<ObjPrimitive<double>*>(AS_PRIMITIVE(args[0]));
		
		return PrimitiveVal(vm.newFloat((double)(lhs->value) + rhs->value));
	}));

	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operator-", "float"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 1);
        assert(primitive->primitiveType == PrimitiveType::INT);
		assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(primitive);
		ObjPrimitive<double>* rhs = static_cast<ObjPrimitive<double>*>(AS_PRIMITIVE(args[0]));
		
		return PrimitiveVal(vm.newFloat((double)(lhs->value) - rhs->value));
	}));

	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operatorbool"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 0);
		assert(primitive->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(primitive);
		
		return PrimitiveVal(vm.newBool(lhs->value));
	}));

	EXPECT_TRUE(vm.linkMethodNative("int", vm.getFunctionName("operator==", "int"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 1);
        assert(primitive->primitiveType == PrimitiveType::INT);
		assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(primitive);
		ObjPrimitive<int64_t>* rhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
		
		return PrimitiveVal(vm.newBool(lhs->value == rhs->value));
	}));

	EXPECT_TRUE(vm.linkMethodNative("float", vm.getFunctionName("operator+", "float"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 1);
		assert(primitive->primitiveType == PrimitiveType::FLOAT);
        assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive<double>* lhs = static_cast<ObjPrimitive<double>*>(primitive);
		ObjPrimitive<double>* rhs = static_cast<ObjPrimitive<double>*>(AS_PRIMITIVE(args[0]));
		
		return PrimitiveVal(vm.newFloat(lhs->value + rhs->value));
	}));

	EXPECT_TRUE(vm.linkMethodNative("float", vm.getFunctionName("operator-", "float"), [] (VirtualMachine& vm, int argCount, ObjPrimitiveType* primitive, Value* args) {
		assert(argCount == 1);
		assert(primitive->primitiveType == PrimitiveType::FLOAT);
        assert(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive<double>* lhs = static_cast<ObjPrimitive<double>*>(primitive);
		ObjPrimitive<double>* rhs = static_cast<ObjPrimitive<double>*>(AS_PRIMITIVE(args[0]));
		
		return PrimitiveVal(vm.newFloat(lhs->value - rhs->value));
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


TEST(TEST_VM, IfTest)
{
	TEST_VM_TEST("native void t(int f); void f() { int s = 20; if (1 == 1) {s = 10;}; t(s); };};\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 10);

		return NULL_VAL;
	}));
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, IfClassConditionTest)
{
	TEST_VM_TEST("native void t(int f); class TestClass {}; void f() { int s = 20; TestClass oui = new TestClass(); if (oui) {s = 10;}; t(s); };};\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 10);

		return NULL_VAL;
	}));
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, IfNullConditionTest)
{
	TEST_VM_TEST("native void t(int f); class TestClass {}; void f() { int s = 20; TestClass oui; if (oui) {s = 10;}; t(s); };};\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 20);

		return NULL_VAL;
	}));
 
	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, GlobalNativeTest)
{
	TEST_VM_TEST("native float t(int a, int b, int c, float d); void f() { print(t(10, 20, 30, 40.5)); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int", "int", "int", "float"), [] (VirtualMachine& vm, int argCount, Value* args) {
		std::cout << "From native argcount : " << argCount << std::endl; 

		for (int i = 0; i < argCount; ++i)
		{
			vm.printValue(args[i]);
			std::cout << std::endl;
		}
	
		return PrimitiveVal(vm.newFloat(500.5));
	}));

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
		EXPECT_TRUE(IS_PRIMITIVE(*y) && AS_PRIMITIVE(*y)->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(*y));

		EXPECT_EQ(lhs->value, 23);

		*vm.getStaticField("Other", "t") = PrimitiveVal(vm.newInt(123));
		
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

	result = vm.interpretMethodFunction(instance, vm.getFunctionName("update", "float"), {PrimitiveVal(vm.newFloat(625.5))});

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
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive<double>* lhs = static_cast<ObjPrimitive<double>*>(AS_PRIMITIVE(args[0]));
		EXPECT_EQ(lhs->value, 510.23);

		return NULL_VAL;
	}));

	result = vm.interpretMethodFunction(instance, vm.getFunctionName("update", "float"), {PrimitiveVal(vm.newFloat(510.23))});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, IntOperatorPlusMinusFloatTest)
{
	TEST_VM_TEST("native void t(float a, float b); void f() { t(10 + 40.5, 10 - 40.5); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "float", "float"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 2);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);
		EXPECT_TRUE(IS_PRIMITIVE(args[1]) && AS_PRIMITIVE(args[1])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive<double>* lhs = static_cast<ObjPrimitive<double>*>(AS_PRIMITIVE(args[0]));
		ObjPrimitive<double>* rhs = static_cast<ObjPrimitive<double>*>(AS_PRIMITIVE(args[1]));
	
		EXPECT_EQ(lhs->value, 50.5);
		EXPECT_EQ(rhs->value, -30.5);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, CustomOperatorPlusTest)
{
	TEST_VM_TEST("native void t(float a); class Test { int x = 20; float operator+(float y) {return x + y;}; }; void f() {Test oui = new Test(); t(oui + 10.0); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "float"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::FLOAT);

		ObjPrimitive<double>* lhs = static_cast<ObjPrimitive<double>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 30.0);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, boolTest)
{
	TEST_VM_TEST("native void t(bool b); void f() {t(true); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "bool"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::BOOL);

		ObjPrimitive<bool>* lhs = static_cast<ObjPrimitive<bool>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, true);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, operatorBoolTest)
{
	TEST_VM_TEST("native void t(bool b, int c); native void h(bool b); void f() { t(10, 10); h(0); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "bool", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 2);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::BOOL);
		EXPECT_TRUE(IS_PRIMITIVE(args[1]) && AS_PRIMITIVE(args[1])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<bool>* lhs = static_cast<ObjPrimitive<bool>*>(AS_PRIMITIVE(args[0]));
		ObjPrimitive<int64_t>* rhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[1]));
	
		EXPECT_EQ(lhs->value, true);
		EXPECT_EQ(rhs->value, 10);

		return NULL_VAL;
	}));

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("h", "bool"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::BOOL);

		ObjPrimitive<bool>* lhs = static_cast<ObjPrimitive<bool>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, false);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, operatorBoolIfTest)
{
	TEST_VM_TEST("native void t(int c); void f() { int z = 0; if (10 < 20) {z = 20; }; t(z); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 20);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, operatorBoolCustomTest)
{
	TEST_VM_TEST("native void h(bool b); class TestClass { bool operatorbool() { return true; }; }; void f() { h(new TestClass()); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("h", "bool"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::BOOL);

		ObjPrimitive<bool>* lhs = static_cast<ObjPrimitive<bool>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, true);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, unaryOperatorTest)
{
	TEST_VM_TEST("native void t(int c); void f() { t(-10);};\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, -10);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, methodCallInClassTest)
{
	TEST_VM_TEST("class TestClass { native void t(int c); void meth() { t(10); }; }; void f() { TestClass oui = new TestClass(); oui.meth(); };\n");

	EXPECT_TRUE(vm.linkMethodNative("TestClass", vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, ObjInstance* instance, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 10);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

TEST(TEST_VM, fibTest)
{
	TEST_VM_TEST("int fib(int n) {if (n < 2) {return n;}; return fib(n-1) + fib(n-2);}; native void t(int n); void f() { int z = fib(31); t(z); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 1346269);

		return NULL_VAL;
	}));

	result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

	EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
	EXPECT_EQ(vm.stackSize(), 0);
}

static void fibNativeBench(benchmark::State& state)
{
	TEST_VM_TEST("native int fib(int n); native void t(int n); void f() { t(fib(31)); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("fib", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));

		const auto fib = [](int64_t n) {
			const auto fib_impl = [](int64_t n, const auto& impl) -> int64_t
			{
				if (n < 2)
				{
					return n;
				}
				else
				{
					return impl(n - 2, impl) + impl(n - 1, impl);
				}
			};
			return fib_impl(n, fib_impl);
		};

		return PrimitiveVal(vm.newInt(fib(lhs->value)));
	}));

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 1346269);

		return NULL_VAL;
	}));

	for (auto _ : state)
	{
		result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

		EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
		EXPECT_EQ(vm.stackSize(), 0);
	}
}

BENCHMARK(fibNativeBench)->Unit(benchmark::kSecond);

static void fibNoNativeBench(benchmark::State& state)
{
	TEST_VM_TEST("int fib(int n) {if (n < 2) {return n;}; return fib(n-1) + fib(n-2);}; native void t(int n); void f() { t(fib(31)); };\n");

	EXPECT_TRUE(vm.linkGlobalNative(vm.getFunctionName("t", "int"), [] (VirtualMachine& vm, int argCount, Value* args) {
		EXPECT_TRUE(argCount == 1);
		EXPECT_TRUE(IS_PRIMITIVE(args[0]) && AS_PRIMITIVE(args[0])->primitiveType == PrimitiveType::INT);

		ObjPrimitive<int64_t>* lhs = static_cast<ObjPrimitive<int64_t>*>(AS_PRIMITIVE(args[0]));
	
		EXPECT_EQ(lhs->value, 1346269);

		return NULL_VAL;
	}));

	for (auto _ : state)
	{
		result = vm.interpretGlobalFunction(vm.getFunctionName("f"), {});

		EXPECT_EQ(result, Pomme::InterpretResult::INTERPRET_OK);
		EXPECT_EQ(vm.stackSize(), 0);
	}
}

BENCHMARK(fibNoNativeBench)->Unit(benchmark::kSecond);

TEST(TEST_VM, benchmarkTest)
{
	::benchmark::RunSpecifiedBenchmarks("fibNativeBench");
	::benchmark::RunSpecifiedBenchmarks("fibNoNativeBench");
}


#undef TEST_VM_TEST