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
	std::cout << "File : " << str << std::endl;\
	std::cout << "Text : " << text << std::endl;\
	EXPECT_EQ(text, str);\


TEST(TEST_LEXER_PARSER, BasicClass)
{
	TEST_PARSER_FILE("class test { };\n", "tests/basicClass.txt");
}

TEST(TEST_LEXER_PARSER, BasicFuncs)
{
	TEST_PARSER_FILE("void func() {}; void func(int64_t a, int64_t b) {};\n", "tests/basicFuncs.txt");
}

TEST(TEST_LEXER_PARSER, BasicDeclsFuncs)
{
	TEST_PARSER_FILE("void func() { int64_t a; int64_t a = 5; float b; float b = 5; };\n", "tests/basicDeclsFuncs.txt");
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
	TEST_PARSER_FILE("class test{ int funcTest(){}; int testAtt; }; void test1(){};\n", "tests/1Class1Method1Function.txt");
}

TEST(TEST_LEXER_PARSER, 3Functions1Return)
{
	TEST_PARSER_FILE("void test2(){}; void test1(){}; int64_t test1(){ return 0;};\n", "tests/3Functions1Return.txt");
}

TEST(TEST_LEXER_PARSER, 2Functions)
{
	TEST_PARSER_FILE("void f(){};  void g(){  f(); };\n", "tests/2Functions.txt");
}

TEST(TEST_LEXER_PARSER, 1Function1Member)
{
	TEST_PARSER_FILE("int64_t f(){ return 3;}; class main{ int64_t a = f(); };\n", "tests/1Function1Member.txt");
}

TEST(TEST_LEXER_PARSER, AccessMember)
{
	TEST_PARSER_FILE("Test glob() { return new Test() ; }; class Test{ int64_t b = 8; Test t = new Test(); }; void main(){ Test t = new Test(); int64_t a = t.b; int64_t c = t.t.b; int64_t y = t[50]; t.operator+=(); t.operator*(); t.operatorbool(); t.operator++(); t.t.salut(); t.t.salut().a; glob().t; };\n", "tests/AccesMember.txt");
}

TEST(TEST_LEXER_PARSER, TestIfElse)
{
	TEST_PARSER_FILE("void main(){ int64_t a; if(true){ a = 2; }else{ a = 3; }; };\n", "tests/TestIfElse.txt");
}

TEST(TEST_LEXER_PARSER, TestIf)
{
	TEST_PARSER_FILE("void main(){ int64_t a; if(true){ a = 2; }; };\n", "tests/TestIf.txt");
}

TEST(TEST_LEXER_PARSER, TestWhile)
{
	TEST_PARSER_FILE("void main(){ while(true){ print(\"Hello World!\"); }; };\n", "tests/TestWhile.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator1)
{
	TEST_PARSER_FILE("void main(){ int64_t b = 2; int64_t a = 1; a <<= b; a >>= b; b++; ++b; b--; --b;};\n", "tests/TestOperator1.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator2)
{
	TEST_PARSER_FILE("void main(){ bool a = 8 >= 7; a = 8 <= 7; a = 8 > 7; a = 8 < 7; };\n", "tests/TestOperator2.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator3)
{
	TEST_PARSER_FILE("void main(){ int64_t a = 8*7;  a = 8 + 7;  a = 8 - 7;  a = 8/8; };\n", "tests/TestOperator3.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator4)
{
	TEST_PARSER_FILE("void main(){ int64_t b = 2; int64_t a = 111000 >> 2; a = 111000 << 2; a = 4 % 2; a += b; a -= b; a *= b; a /= b; };\n", "tests/TestOperator4.txt");
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
	TEST_PARSER_FILE("void main(){ int64_t a = 0; bool b = a == 1; b = a != 0;  b = !a;  };\n", "tests/TestOperator7.txt");
}

TEST(TEST_LEXER_PARSER, TestOperator8)
{
	TEST_PARSER_FILE("void main(){ int64_t a = 1111; int64_t b = ~a;};\n", "tests/TestOperator8.txt");
}

TEST(TEST_LEXER_PARSER, TestNull)
{
	TEST_PARSER_FILE("class Array{ Array arrayTest = new Array(); }; void test(){ Array a = null; };\n", "tests/TestNull.txt");
}

TEST(TEST_LEXER_PARSER, TestThis)
{
	TEST_PARSER_FILE("class Array{ int a; void test(){ a = 10; };  void test2(){ this.test(); }; };\n", "tests/TestThis.txt");
}

TEST(TEST_LEXER_PARSER, TestClassSpecific)
{
	TEST_PARSER_FILE("class Array extends ArrayC { override int test(){ super.test(); }; static void x(){}; private void y(){}; protected void z(){}; };\n", "tests/TestClassSpecific.txt");
}

TEST(TEST_LEXER_PARSER, TestConst)
{
	TEST_PARSER_FILE("void constTest(){ const int64_t a = 8; };\n", "tests/TestConst.txt");
}

TEST(TEST_LEXER_PARSER, TestNativeGlobalFunction)
{
	TEST_PARSER_FILE("native void f();\n", "tests/TestNativeGlobalFunction.txt");
}

TEST(TEST_LEXER_PARSER, TestConstructorDestructor)
{
	TEST_PARSER_FILE("class Destr{ Destr(int a) {}; ~Destr() {}; };\n", "tests/TestConstructorDestructor.txt");
}

TEST(TEST_LEXER_PARSER, TestTypeDef)
{
	TEST_PARSER_FILE("class Test {}; enum TestEnum {}; typedef TestEnum MyEnum;\n", "tests/TestTypeDef.txt");
}

TEST(TEST_LEXER_PARSER, TestHeaders)
{
	TEST_PARSER_FILE("class Array{ int b; int test(int a, int c, int d){};  void test2(int a){}; };\n", "tests/TestHeaders.txt");
}


#undef TEST_PARSER_FILE