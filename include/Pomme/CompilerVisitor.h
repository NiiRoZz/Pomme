#pragma once

#include "PommeLexerVisitor.h"
#include "Chunk.h"
#include "Object.h"
#include "Common.h"

#include <array>

namespace Pomme
{
	class VirtualMachine;

	struct Local
	{
		std::string name;
		int depth;
	};

	class CompilerVisitor : public PommeLexerVisitor
	{
	private:
		struct Constructor
		{
			bool generateSuperCall;
			ObjFunction* function;
		};

	public:
		CompilerVisitor(VirtualMachine &vm);

		Chunk* currentChunk();

	public:
		// Inherited via TestLexerVisitor
		void visit(SimpleNode *node, void * data);
		void visit(ASTPommeInput *node, void * data);
		void visit(ASTPommeIdent *node, void * data);
		void visit(ASTPommeIdentOp *node, void * data);
		void visit(ASTPommeInt *node, void * data);
		void visit(ASTPommeFloat *node, void * data);
		void visit(ASTPommeString *node, void * data);
		void visit(ASTPommeScopes *node, void * data);
		void visit(ASTPommeScinil *node, void * data);
		void visit(ASTPommeTypeDef *node, void * data);
		void visit(ASTPommeClass *node, void * data);
		void visit(ASTPommeClassChild *node, void * data);
		void visit(ASTPommeModdedClass *node, void * data);
		void visit(ASTPommeDecls *node, void * data);
		void visit(ASTPommeDnil *node, void * data);
		void visit(ASTPommeMethode *node, void * data);
		void visit(ASTPommeMethodeNative *node, void * data);
		void visit(ASTPommeIdentFuncs *node, void * data);
		void visit(ASTPommeStatic *node, void * data);
		void visit(ASTPommeSnil *node, void * data);
		void visit(ASTPommePublic *node, void * data);
		void visit(ASTPommePrivate *node, void * data);
		void visit(ASTPommeProtected *node, void * data);
		void visit(ASTPommeVinil *node, void * data);
		void visit(ASTPommeOverride *node, void * data);
		void visit(ASTPommeOnil *node, void * data);
		void visit(ASTPommeEnum *node, void * data);
		void visit(ASTPommeExtendsEnum *node, void * data);
		void visit(ASTPommeModdedEnum *node, void * data);
		void visit(ASTPommeDeclEnums *node, void * data);
		void visit(ASTPommeEnnil *node, void * data);
		void visit(ASTPommeEnumAssign *node, void * data);
		void visit(ASTPommeEnumDefault *node, void * data);
		void visit(ASTPommeGlobalFunction *node, void * data);
		void visit(ASTPommeGlobalFunctionNative *node, void * data);
		void visit(ASTPommeInstrs *node, void * data);
		void visit(ASTPommeInil *node, void * data);
		void visit(ASTPommeIncrPre *node, void * data);
		void visit(ASTPommeDecrPre *node, void * data);
		void visit(ASTPommeDelete *node, void * data);
		void visit(ASTPommeReturn *node, void * data);
		void visit(ASTPommeWhile *node, void * data);
		void visit(ASTPommeBreak *node, void * data);
		void visit(ASTPommeIf *node, void * data);
		void visit(ASTPommePrint *node, void * data);
		void visit(ASTPommeSwitch *node, void * data);
		void visit(ASTPommeAssign *node, void * data);
		void visit(ASTPommeAddEq *node, void * data);
		void visit(ASTPommeMinusEq *node, void * data);
		void visit(ASTPommeDivEq *node, void * data);
		void visit(ASTPommeMultEq *node, void * data);
		void visit(ASTPommeOrEq *node, void * data);
		void visit(ASTPommeAndEq *node, void * data);
		void visit(ASTPommeShiftLEq *node, void * data);
		void visit(ASTPommeShiftREq *node, void * data);
		void visit(ASTPommeIncrPost *node, void * data);
		void visit(ASTPommeDecrPost *node, void * data);
		void visit(ASTPommeCases *node, void * data);
		void visit(ASTPommeDefault *node, void * data);
		void visit(ASTPommeSwinil *node, void * data);
		void visit(ASTPommeCase *node, void * data);
		void visit(ASTPommeListExp *node, void * data);
		void visit(ASTPommeExnil *node, void * data);
		void visit(ASTPommeVarDecls *node, void * data);
		void visit(ASTPommeVariable *node, void * data);
		void visit(ASTPommeConstant *node, void * data);
		void visit(ASTPommeOmega *node, void * data);
		void visit(ASTPommeHeaders *node, void * data);
		void visit(ASTPommeEnil *node, void * data);
		void visit(ASTPommeConstHeader *node, void * data);
		void visit(ASTPommeHeader *node, void * data);
		void visit(ASTPommeVoidType *node, void * data);
		void visit(ASTPommeConstructor *node, void * data);
		void visit(ASTPommeDestructor *node, void * data);
		void visit(ASTPommeAnd *node, void * data);
		void visit(ASTPommeOr *node, void * data);
		void visit(ASTPommeEQ *node, void * data);
		void visit(ASTPommeNEQ *node, void * data);
		void visit(ASTPommeGT *node, void * data);
		void visit(ASTPommeGET *node, void * data);
		void visit(ASTPommeLT *node, void * data);
		void visit(ASTPommeLET *node, void * data);
		void visit(ASTPommeAdd *node, void * data);
		void visit(ASTPommeMinus *node, void * data);
		void visit(ASTPommeShiftR *node, void * data);
		void visit(ASTPommeShiftL *node, void * data);
		void visit(ASTPommeMult *node, void * data);
		void visit(ASTPommeDiv *node, void * data);
		void visit(ASTPommeModulo *node, void * data);
		void visit(ASTPommeUnary *node, void * data);
		void visit(ASTPommeNot *node, void * data);
		void visit(ASTPommeTilde *node, void * data);
		void visit(ASTPommeNew *node, void * data);
		void visit(ASTPommeTrue *node, void * data);
		void visit(ASTPommeFalse *node, void * data);
		void visit(ASTPommeNull *node, void * data);
		void visit(ASTPommeListAccess *node, void * data);
		void visit(ASTPommeListAccessP *node, void * data);
		void visit(ASTPommeAcnil *node, void * data);
		void visit(ASTPommeAccessMethode *node, void * data);
		void visit(ASTPommeAccessTab *node, void * data);

	private:

		void emitByte(Chunk* chunk, uint8_t byte);
		void emitByte(uint8_t byte);

		void emitBytes(Chunk* chunk, uint8_t byte1, uint8_t byte2);
		void emitBytes(uint8_t byte1, uint8_t byte2);

		void emit16Bits(Chunk* chunk, uint16_t val);
		void emit16Bits(uint16_t val);

		void emit32Bits(Chunk* chunk, uint8_t* val);
		void emit32Bits(uint8_t* val);

		void emit64Bits(Chunk* chunk, uint8_t* val);
		void emit64Bits(uint8_t* val);

		void emitInt(uint64_t val);
		void emitFloat(double val);

		void emitReturn();

		uint64_t emitJump(uint8_t instruction);
		void patchJump(uint64_t offset);

		void emitLoop(uint64_t loopStart);

		void emitDefaultValue(const std::string& typeName);

		void endCompiler();
		void emitConstant(const Value& value);
		uint8_t makeConstant(const Value& value);

		void beginScope();
		void endScope();

		void accessProperty(Node* left, Node* middle, Node* right, void * data);
		void method(SimpleNode *node, const std::string& ident, const std::string& methodIdent, uint16_t index, bool constructor, bool generateSuperCall);
		
		void unaryOperator(SimpleNode *node, uint16_t index, bool native);
		void binaryOperator(SimpleNode *node, uint16_t index, bool native);

		int addLocal(const std::string& name);
		void namedVariable(const std::string& name, bool assign);
	private:
		VirtualMachine& m_Vm;
	
		ObjFunction* function;
		int line;

		std::array<Local, UINT8_COUNT> locals;
  		int localCount;

		int scopeDepth;

		bool m_InClass;
		bool m_InNativeClass;
		bool m_InMethod;

		std::string m_SuperClass;

		Chunk m_ConstructorChunk;
		bool m_ConstructorInit;
		std::vector<Constructor> m_ConstructorFunctions;

		std::vector<std::vector<uint64_t>> scopeBreakable;
	};
}