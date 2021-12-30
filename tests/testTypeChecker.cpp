#include "gtest/gtest.h"

#include "PommeLexer.h"
#include "TypeChecker.h"
#include "PommeLexerTokenManager.h"
#include "MyErrorHandler.h"

#include <iostream>
#include <fstream>

using namespace Pomme;

#define TEST_TYPECHECKER_TEST(testString) \
    std::ifstream t(std::string(POMME_BIN_PATH) + "std.pomme");\
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());\
    std::size_t countLinesStr = std::count_if(str.begin(), str.end(), [](char i){return i == '\n';});\
    std::string testStr = testString;\
    std::size_t countLinesTestStr = std::count_if(testStr.begin(), testStr.end(), [](char i){return i == '\n';});\
	std::string s = str + testStr;\
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
    std::vector<ErrorFile> compileFiles;\
    compileFiles.emplace_back(std::string(POMME_BIN_PATH) + "std.pomme", 1u, countLinesStr);\
    compileFiles.emplace_back("CustomString", countLinesStr, countLinesStr + countLinesTestStr );\
    TypeChecker typeChecker(compileFiles);\
    TypeCheckerVisitor visitor = typeChecker.typeCheck(tree);\
    std::cout << text << std::endl;\

TEST(TEST_TYPECHECKER, ClassComplete)
{
    TEST_TYPECHECKER_TEST("class test { int a = 8;  bool b = true; void meth(){ int b = 7; }; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, FileComplete)
{
    TEST_TYPECHECKER_TEST("void meth(){};  void xd(int j){}; class test { int a = 8; bool b = true; void meth(int abc){ bool b = false; }; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, Class)
{
    TEST_TYPECHECKER_TEST("class A { int a = 1;}; class B { int a = 1;}; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassAttributeRedefinition)
{
    TEST_TYPECHECKER_TEST("class test { int a; int a;}; \n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassRedefinition)
{
    TEST_TYPECHECKER_TEST("class test {}; class test {};\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, GlobalFunction)
{
    TEST_TYPECHECKER_TEST(" void meth(int k){ int a; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassMethodRedefinition)
{
    TEST_TYPECHECKER_TEST("class test { void meth(){}; void meth(){}; }; \n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, GlobalFunctionRedefinition)
{
    TEST_TYPECHECKER_TEST("void meth(){}; void meth(){};\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, GlobalFunctionRedefinitionWithDifferentType)
{
    TEST_TYPECHECKER_TEST("void meth(){}; int meth(){};\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, CompleteClass)
{
    TEST_TYPECHECKER_TEST("class test { int a; void meth(int n){}; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, GlobalFunctionOverloading)
{
    TEST_TYPECHECKER_TEST(" int meth(int n){}; int meth(){};\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ParametersRedefinitionWithDifferentType)
{
    TEST_TYPECHECKER_TEST(" int meth(int n, bool n){};\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, FunctionRedefinitionWithDifferentType)
{
    TEST_TYPECHECKER_TEST(" int meth(int n){}; void meth(int n){};\n");
    
    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, TestIndex)
{
    TEST_TYPECHECKER_TEST("class Test{ int a = 8; int j = 7; int meth(int n){}; int j(){}; };\n");
    
    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, Constant)
{
    TEST_TYPECHECKER_TEST("class test { const int k = 10;  const int v = 8;}; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, StaticMethod)
{
    TEST_TYPECHECKER_TEST("class test { static int test(){}; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test")->second.methods.find("test!")->second.keywords.count("static"));
}

TEST(TEST_TYPECHECKER, VisibilityMethod)
{
    TEST_TYPECHECKER_TEST("class test { public int testPublic(){}; private int testPrivate(){}; protected int testProtected(){}; int testPrivate2(){}; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test")->second.methods.find("testPublic!")->second.keywords.count("public"));
    EXPECT_TRUE(visitor.classMap.find("test")->second.methods.find("testPrivate!")->second.keywords.count("private"));
    EXPECT_TRUE(visitor.classMap.find("test")->second.methods.find("testPrivate2!")->second.keywords.count("private"));
    EXPECT_TRUE(visitor.classMap.find("test")->second.methods.find("testProtected!")->second.keywords.count("protected"));

}
TEST(TEST_TYPECHECKER, OverrideMethod)
{
    TEST_TYPECHECKER_TEST("class test { override int f(){}; }; \n");

    EXPECT_TRUE(visitor.errors.size() > 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test")->second.methods.find("f!")->second.keywords.count("override"));
}
TEST(TEST_TYPECHECKER, StaticVisibilityMethod)
{
    TEST_TYPECHECKER_TEST("class test { static public int test(){}; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }

    EXPECT_TRUE(visitor.classMap.find("test")->second.methods.find("test!")->second.keywords.count("static"));
    EXPECT_TRUE(visitor.classMap.find("test")->second.methods.find("test!")->second.keywords.count("public"));
}

TEST(TEST_TYPECHECKER, ExtendedClass) {
    TEST_TYPECHECKER_TEST("class test { int t; void t2(){}; }; class test2 extends test {}; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test2")->second.keywords.count("extends"));
    EXPECT_TRUE(visitor.classMap.find("test2")->second.methods.count("t2!"));
}
TEST(TEST_TYPECHECKER, ExtendingNonExistingClass) {
    TEST_TYPECHECKER_TEST("class test extends t2{}; \n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, OverridingWithoutExtends) {
    TEST_TYPECHECKER_TEST("class test{ override void x(){}; }; \n");

    EXPECT_TRUE(visitor.errors.size() > 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, OverridingWithoutDefinitionInParent) {
    TEST_TYPECHECKER_TEST("class test {  void a(){}; }; class test2 extends test{ override void b() {}; }; \n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, OverridingAMethod) {
    TEST_TYPECHECKER_TEST("class test {  void a(){}; }; class test2 extends test{ override void a() {}; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, RedefinitionOfVarFromParentClass) {
    TEST_TYPECHECKER_TEST("class test{ int a; }; class test2 extends test { bool a;  bool b; };\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);

    EXPECT_TRUE(visitor.classMap.find("test")->second.attributes.count("a"));
    EXPECT_TRUE(visitor.classMap.find("test2")->second.attributes.count("a"));
    EXPECT_TRUE(visitor.classMap.find("test2")->second.attributes.find("a")->second.variableType == "int");
    EXPECT_TRUE(visitor.classMap.find("test2")->second.attributes.count("b"));
}

TEST(TEST_TYPECHECKER, AccessToNonExistingMethod) {
    TEST_TYPECHECKER_TEST("class test{ void x(){ op(10); }; };\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, AccessToExistingMethod) {
    TEST_TYPECHECKER_TEST("class test{ void k(){}; void op(int x){}; void x(){ op(10); }; };\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, CallingGlobalFunctionNotDefined) {
    TEST_TYPECHECKER_TEST("void x(){ op(10); };\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, CallingFunctionOnInstanceReturn) {
    TEST_TYPECHECKER_TEST("x op(){}; class x{ void t(){}; void meth(){ op().t(); }; };\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, CallingFunctionOnInstanceReturnNotExisting) {
    TEST_TYPECHECKER_TEST("x op(){}; class x{ void meth(){ op().t(); }; };\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, MultipleAccessProperty) {
    TEST_TYPECHECKER_TEST("x op(){}; class x{ x t(){}; void meth(){ op().t().t(); }; };\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, MultipleAccessP) {
    TEST_TYPECHECKER_TEST("x op(){}; class x{ x t(){}; void meth(){ op().t().t().t(); };};\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, LocalsDefinition) {
    TEST_TYPECHECKER_TEST("class x{ void meth(){ int a; int b; }; };\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, NotDefinedVariableInFunction) {
    TEST_TYPECHECKER_TEST("class x{ void meth(){ k = 8; }; };\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 2);
}

TEST(TEST_TYPECHECKER, RedefinitionOfLocalInGlobal) {
    TEST_TYPECHECKER_TEST("void meth(){ int x; int x; };\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, RedefinitionOfLocalInFunction) {
    TEST_TYPECHECKER_TEST("class x{ void meth(){ int x; int x; }; };\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, DefinedVariableInLocals) {
    TEST_TYPECHECKER_TEST("class x{ void meth(){ int x; x = 8; }; };\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, DefinedVariableInAttribute) {
    TEST_TYPECHECKER_TEST("class x{ int x; int y; void meth(){ x = 8; y = 10; }; };\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, DefinedVariableInHeader) {
    TEST_TYPECHECKER_TEST("class x{ void meth(int x){ x = 8; }; };\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, RedefinedVariableInHeader) {
    TEST_TYPECHECKER_TEST("class x{ void meth(int y, int y){}; };\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, MethodNameSameAsClass) {
    TEST_TYPECHECKER_TEST("class x { void x(int x, int y) {}; };\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, Constructor) {
    TEST_TYPECHECKER_TEST("class x { x(int x, int y) {}; x() {}; };\n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ConstructorNotCorrectName) {
    TEST_TYPECHECKER_TEST("class x { z(int x, int y) {}; x() {}; };\n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, StaticAttribute)
{
    TEST_TYPECHECKER_TEST("class test { static int test; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_TRUE(visitor.classMap.find("test")->second.staticAttributes.count("test"));
}

TEST(TEST_TYPECHECKER, StaticAttributeAlreadyDefined)
{
    TEST_TYPECHECKER_TEST("class test { static int test; int test; }; \n");

    EXPECT_EQ(visitor.errors.size(), 1);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, TestAssignCorrectClass)
{
    TEST_TYPECHECKER_TEST("class A {}; class B {}; class test { void meth() { A a; a = new A(); }; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, TestAssignNotCorrectClass)
{
    TEST_TYPECHECKER_TEST("class A {}; class B {}; class test { void meth() { A a; a = new B(); }; }; \n");

    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, TestCreateCorrectClass)
{
    TEST_TYPECHECKER_TEST("class A {}; class B {}; class test { void meth() { A a = new A(); }; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, TestCreateNotCorrectClass)
{
    TEST_TYPECHECKER_TEST("class A {}; class B {}; class test { void meth() { A a = new B(); }; }; \n");

    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, TestOperatorPlus)
{
    TEST_TYPECHECKER_TEST("class test { void meth() { int a = 5 + 5; }; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassDefineAutomate)
{
    TEST_TYPECHECKER_TEST("class test extends test2{}; class test2{}; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    auto it = visitor.classMap.find("test");
    auto ot = visitor.classMap.find("test2");
    EXPECT_NE(it, visitor.classMap.end());
    EXPECT_NE(ot, visitor.classMap.end());
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassDefineAutomate2)
{
    TEST_TYPECHECKER_TEST("class test{ test2 x; }; class test2{}; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    auto it = visitor.classMap.find("test");
    auto ot = visitor.classMap.find("test2");
    EXPECT_NE(it, visitor.classMap.end());
    EXPECT_NE(ot, visitor.classMap.end());
    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, ClassDefineAutomate3)
{
    TEST_TYPECHECKER_TEST("class test{ test2 x; test3 y; }; class test2{}; class test3{};\n");

    auto it = visitor.classMap.find("test");
    auto ot = visitor.classMap.find("test2");
    auto ut = visitor.classMap.find("test3");
    EXPECT_NE(it, visitor.classMap.end());
    EXPECT_NE(ot, visitor.classMap.end());
    EXPECT_NE(ut, visitor.classMap.end());

    for(const auto& error : visitor.errors ){
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}

TEST(TEST_TYPECHECKER, ClassDefineAutomate4)
{
    TEST_TYPECHECKER_TEST("class test1{}; " // 0
                          "class test2{}; " // 1
                          "class test extends test3 {}; " // 2
                          "class test3 extends test1{ test2 x;};\n"); // 3

    auto ut = visitor.classMap.find("test");
    auto it = visitor.classMap.find("test1");
    auto ot = visitor.classMap.find("test2");
    auto yt = visitor.classMap.find("test3");
    EXPECT_NE(it, visitor.classMap.end());
    EXPECT_NE(ot, visitor.classMap.end());
    EXPECT_NE(ut, visitor.classMap.end());
    EXPECT_NE(yt, visitor.classMap.end());

    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}

TEST(TEST_TYPECHECKER, CheckOrderDefinition)
{
    TEST_TYPECHECKER_TEST("class test{ int x; void methode(){ meth(); }; }; void meth(){};\n"); // if no dependance -> global first

    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}

TEST(TEST_TYPECHECKER, EnumAsAttribute)
{
    TEST_TYPECHECKER_TEST("enum test{}; class test2{ test x; };\n");

    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}

TEST(TEST_TYPECHECKER, EnumRedefinition)
{
    TEST_TYPECHECKER_TEST("enum test{}; enum test{};\n");

    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, EnumExtends)
{
    TEST_TYPECHECKER_TEST("enum test extends test1{}; enum test1{};\n");

    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}

TEST(TEST_TYPECHECKER, ExtendingNonExistingEnum)
{
    TEST_TYPECHECKER_TEST("enum test extends testX{};\n");

    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, Loop)
{
    TEST_TYPECHECKER_TEST("class test extends test2{}; class test2 extends test{};\n");

    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, EnumMemberRedefinition) {
    TEST_TYPECHECKER_TEST("enum test{ a, a};\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 1);
}

TEST(TEST_TYPECHECKER, EnumDefault) {
    TEST_TYPECHECKER_TEST("enum test{ a, b, c};\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}

TEST(TEST_TYPECHECKER, EnumAssign) {
    TEST_TYPECHECKER_TEST("enum test{ a, b, c = 20};\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}

TEST(TEST_TYPECHECKER, EnumAssignDefault) {
    TEST_TYPECHECKER_TEST("enum test{ a, b, c = 20, d};\n");

    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}
TEST(TEST_TYPECHECKER, SuperNotCallTest) {
    TEST_TYPECHECKER_TEST("class test { int z;  void a(){}; }; class test2 extends test{ void b() { super.z; }; }; \n");

    EXPECT_TRUE(visitor.errors.size() > 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, SuperCallTest) {
    TEST_TYPECHECKER_TEST("class test {  void a(){}; }; class test2 extends test{ void b() { super.a(); }; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, SuperCallOnOverrideTest) {
    TEST_TYPECHECKER_TEST("class test {  void a(){}; }; class test2 extends test{ override void a() { super.a(); }; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}
TEST(TEST_TYPECHECKER, ModdedClassTest) {
    TEST_TYPECHECKER_TEST("class test {  void a(){}; }; modded class test { void b(){}; }; void f() { test a = new test(); a.b(); }; \n");

    EXPECT_EQ(visitor.errors.size(), 0);
    for (const auto &error: visitor.errors) {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, AssignementVarDependance)
{
    TEST_TYPECHECKER_TEST("class test2{ int j = test.k(); }; class test{ static int k(){}; };\n");

    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
    EXPECT_EQ(visitor.errors.size(), 0);
}

TEST(TEST_TYPECHECKER, ConstAssign)
{
    TEST_TYPECHECKER_TEST("void f() {const int f = 5; f = 10; }; \n");

    EXPECT_TRUE(visitor.errors.size() > 0);
    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, SuperCall)
{
    TEST_TYPECHECKER_TEST("void f() { super(); }; \n");

    EXPECT_TRUE(visitor.errors.size() > 0);
    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, SuperCallConstructor)
{
    TEST_TYPECHECKER_TEST("class TestClass { TestClass() { super(); }; }; \n");

    EXPECT_TRUE(visitor.errors.size() > 0);
    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, SuperCallConstructorExtendsIncorrect)
{
    TEST_TYPECHECKER_TEST("class TestClass {}; class OtherClass extends TestClass { OtherClass() {print(10); super(); }; }; \n");

    EXPECT_TRUE(visitor.errors.size() > 0);
    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, SuperCallConstructorExtendsCorrect)
{
    TEST_TYPECHECKER_TEST("class TestClass {}; class OtherClass extends TestClass { OtherClass() {super(); print(10); }; }; \n");

    EXPECT_EQ(visitor.errors.size(), 0u);
    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, SuperCallConstructorExtendsIncorrectParameters)
{
    TEST_TYPECHECKER_TEST("class TestClass {}; class OtherClass extends TestClass { OtherClass() {super(10); print(10); }; }; \n");

    EXPECT_TRUE(visitor.errors.size() > 0);
    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
}

TEST(TEST_TYPECHECKER, SuperCallConstructorFromOtherFunction)
{
    TEST_TYPECHECKER_TEST("class TestClass { TestClass() { print(10); }; }; class OtherClass extends TestClass { void f() { super.TestClass(); }; }; \n");

    EXPECT_TRUE(visitor.errors.size() > 0);
    for(const auto& error : visitor.errors)
    {
        std::cout << error << std::endl;
    }
}