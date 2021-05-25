#include "gtest/gtest.h"

#include "PommeLexer.h"
#include "PommeLexerTokenManager.h"
#include "MyErrorHandler.h"

#include <iostream>
#include <fstream>

using namespace Pomme;

#define TEST_PARSER_FILE(testString, file) \
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
	std::ifstream t(file);\
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());\
	EXPECT_EQ(text, str);\
	std::cout << text << std::endl;


TEST(TEST_LEXER_PARSER, BasicClass)
{
	TEST_PARSER_FILE("class test { };\n", "tests/basicClass.txt");
}

TEST(TEST_LEXER_PARSER, BasicFuncs)
{
	TEST_PARSER_FILE("void func() {}; void func(int a, int b) {};\n", "tests/basicFuncs.txt");
}

TEST(TEST_LEXER_PARSER, BasicDeclsFuncs)
{
	TEST_PARSER_FILE("void func() { int a; int a = 5; int a[2]; float b; float b = 5; float b[5]; };\n", "tests/basicDeclsVars.txt");
}

TEST(TEST_LEXER_PARSER, BasicEnums)
{
	TEST_PARSER_FILE("enum testenum"
	"{"
		"FIRST,"
		"SECOND,"
		"THIRD = 50"
	"};"
	"modded enum testenum" 
	"{"
		"FOUR,"
	"};"
	"enum utest extends testenum"
	"{"
		"FIVE = 5,"
		"SIX,"
	"};\n", "tests/basicEnums.txt");
}

TEST(TEST_LEXER_PARSER, 2Classes)
{
	TEST_PARSER_FILE("class test{}; class test2{};\n", "tests/2Classes.txt");
}

TEST(TEST_LEXER_PARSER, 1Class2Methods)
{
	TEST_PARSER_FILE("class test{ native void f1(); static void f2(){}; };\n", "tests/1Class2Methods.txt");
}

TEST(TEST_LEXER_PARSER, 1Class1Method1Function)
{
	TEST_PARSER_FILE("class test{ void funcTest(){}; }; void test1(){};\n", "tests/1Class1Method1Function.txt");
}

TEST(TEST_LEXER_PARSER, 3Functions1Return)
{
	TEST_PARSER_FILE("void test2(){}; void test1(){}; int test1(){ return 0;};\n", "tests/3Functions1Return.txt");
}

TEST(TEST_LEXER_PARSER, 2Functions)
{
	TEST_PARSER_FILE("void f(){};  void g(){  f(); };\n", "tests/2Functions.txt");
}

TEST(TEST_LEXER_PARSER, 1Function1Member)
{
	TEST_PARSER_FILE("int f(){ return 3;}; class main{ int a = f(); };\n", "tests/1Function1Member.txt");
}

TEST(TEST_LEXER_PARSER, AccesMember)
{
	TEST_PARSER_FILE("class Test{ int b = 8;} void main(){ Test t = new Test(); int a = t.b; };\n", "tests/AccesMember.txt");
}

TEST(TEST_LEXER_PARSER, TestIfElse)
{
	TEST_PARSER_FILE("void main(){ int a; if(true){ a = 2; }else{ a = 3; }; };\n", "tests/TestIfElse.txt");
}

TEST(TEST_LEXER_PARSER, TestIf)
{
	TEST_PARSER_FILE("void main(){ int a; if(true){ a = 2; }; };\n", "tests/TestIf.txt");
}

TEST(TEST_LEXER_PARSER, TestWhile)
{
	TEST_PARSER_FILE("void main(){ while(true){ print(\"Hello World!\"); }; };\n", "tests/TestWhile.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator1)
{
	TEST_PARSER_FILE("void main(){  int b = 2; int a = 1; a <<= b; a >>= b; b++; ++b; b--; --b;};\n", "tests/TestOperator1.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator2)
{
	TEST_PARSER_FILE("void main(){ bool a = 8 >= 7; a = 8 <= 7; a = 8 > 7; a = 8 < 7; };\n", "tests/TestOperator2.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator3)
{
	TEST_PARSER_FILE("void main(){ int a = 8*7;  a = 8 + 7;  a = 8 - 7;  a = 8/8; };\n", "tests/TestOperator3.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator4)
{
	TEST_PARSER_FILE("void main(){ int b = 2; int a = 111 000 >> 2; a = 111 000 << 2; a = 4 % 2; a += b; a -= b; a *= b; a /= b; };\n", "tests/TestOperator4.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator5)
{
	TEST_PARSER_FILE("void main(){ bool b = false; bool a = true; a |= b;  a &= b;  };\n", "tests/TestOperator5.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator6)
{
	TEST_PARSER_FILE("void main(){ bool a = true && false; a = true || false;  };\n", "tests/TestOperator6.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator7)
{
	TEST_PARSER_FILE("void main(){ int a = 0; bool b = a == 1; b = a != 0;  b = !a;  };\n", "tests/TestOperator7.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator8)
{
	TEST_PARSER_FILE("void main(){ int a = 1111; int b = ~a;};\n", "tests/TestOperator8.txt");
}

TEST(TEST_LEXER_PARSER, TestArray1)
{
	TEST_PARSER_FILE("void main(){ int a[10]; a[3] = 2; };\n", "tests/TestArray1.txt");
}

TEST(TEST_LEXER_PARSER, TestArray2)
{
	TEST_PARSER_FILE("void main(){ int a[10-5]; a[3] = 2; };\n", "tests/TestArray2.txt");
}

TEST(TEST_LEXER_PARSER, TestArray3)
{
	TEST_PARSER_FILE("void main(){ int a[10+5]; a[3+2] = 2; };\n", "tests/TestArray3.txt");
}

TEST(TEST_LEXER_PARSER, TestNull)
{
	TEST_PARSER_FILE("class Array{ int array[10]; }; class test{ Array a = new Array(); a.array[3] = 8;  a = null; };\n", "tests/TestNull.txt");
}

TEST(TEST_LEXER_PARSER, TestThis)
{
	TEST_PARSER_FILE("class Array{ int array[10]; void test(){ this.array[2] = 0; };  void test2(){ this.test(); }; };\n", "tests/TestThis.txt");
}

TEST(TEST_LEXER_PARSER, TestClassSpecific)
{
	TEST_PARSER_FILE("class Array extends ArrayC { override void test(){ super.test(); }; static void x(){}; private void y(){}; protected void z(){}; };\n", "tests/TestClassSpecific.txt");
}

TEST(TEST_LEXER_PARSER, TestConst)
{
	TEST_PARSER_FILE("void constTest(){ const int a = 8; };\n", "tests/TestConst.txt");
}

TEST(TEST_LEXER_PARSER, TestNativeGlobalFunction)
{
	TEST_PARSER_FILE("native void f();\n", "tests/TestNativeGlobalFunction.txt");
}

TEST(TEST_LEXER_PARSER, TestConstructorDestructor)
{
	TEST_PARSER_FILE("class Destr{ void Destr(){}; void ~Destr(){}; };\n", "tests/TestConstructorDestructor.txt");
}