#pragma once

#include "PommeLexerVisitor.h"
#include "VM/Chunk.h"
#include "VM/Object.h"
#include "VM/Common.h"

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
		VirtualMachine& m_Vm;

	public:
		CompilerVisitor(VirtualMachine &vm);

		Chunk* currentChunk();

	public:
		// Inherited via TestLexerVisitor
		void visit(SimpleNode *node, void * data);
		void visit(ASTinput *node, void * data);
		void visit(ASTident *node, void * data);
		void visit(ASTidentOp *node, void * data);
		void visit(ASTpommeInt *node, void * data);
		void visit(ASTpommeFloat *node, void * data);
		void visit(ASTpommeString *node, void * data);
		void visit(ASTscopes *node, void * data);
		void visit(ASTscinil *node, void * data);
		void visit(ASTpommeTypeDef *node, void * data);
		void visit(ASTpommeClass *node, void * data);
		void visit(ASTpommeClassChild *node, void * data);
		void visit(ASTpommeModdedClass *node, void * data);
		void visit(ASTdecls *node, void * data);
		void visit(ASTdnil *node, void * data);
		void visit(ASTpommeMethode *node, void * data);
		void visit(ASTpommeMethodeNative *node, void * data);
		void visit(ASTidentFuncs *node, void * data);
		void visit(ASTpommeStatic *node, void * data);
		void visit(ASTsnil *node, void * data);
		void visit(ASTpommePublic *node, void * data);
		void visit(ASTpommePrivate *node, void * data);
		void visit(ASTpommeProtected *node, void * data);
		void visit(ASTvinil *node, void * data);
		void visit(ASTpommeOverride *node, void * data);
		void visit(ASTonil *node, void * data);
		void visit(ASTpommeEnum *node, void * data);
		void visit(ASTpommeExtendsEnum *node, void * data);
		void visit(ASTpommeModdedEnum *node, void * data);
		void visit(ASTdeclenums *node, void * data);
		void visit(ASTennil *node, void * data);
		void visit(ASTenumassign *node, void * data);
		void visit(ASTenumdefault *node, void * data);
		void visit(ASTpommeGlobalFunction *node, void * data);
		void visit(ASTpommeGlobalFunctionNative *node, void * data);
		void visit(ASTinstrs *node, void * data);
		void visit(ASTinil *node, void * data);
		void visit(ASTincrementPre *node, void * data);
		void visit(ASTdecrementPre *node, void * data);
		void visit(ASTpommeReturn *node, void * data);
		void visit(ASTpommeWhile *node, void * data);
		void visit(ASTpommeBreak *node, void * data);
		void visit(ASTpommeIf *node, void * data);
		void visit(ASTpommePrint *node, void * data);
		void visit(ASTpommeSwitch *node, void * data);
		void visit(ASTassignement *node, void * data);
		void visit(ASTaddeq *node, void * data);
		void visit(ASTminuseq *node, void * data);
		void visit(ASTdiveq *node, void * data);
		void visit(ASTmulteq *node, void * data);
		void visit(ASToreq *node, void * data);
		void visit(ASTandeq *node, void * data);
		void visit(ASTshiftleq *node, void * data);
		void visit(ASTshiftreq *node, void * data);
		void visit(ASTincrementPost *node, void * data);
		void visit(ASTdecrementPost *node, void * data);
		void visit(ASTpommeCases *node, void * data);
		void visit(ASTpommeDefault *node, void * data);
		void visit(ASTswinil *node, void * data);
		void visit(ASTpommeCase *node, void * data);
		void visit(ASTlistexp *node, void * data);
		void visit(ASTexnil *node, void * data);
		void visit(ASTvarDecls *node, void * data);
		void visit(ASTpommeVariable *node, void * data);
		void visit(ASTpommeConstant *node, void * data);
		void visit(ASTomega *node, void * data);
		void visit(ASTheaders *node, void * data);
		void visit(ASTenil *node, void * data);
		void visit(ASTheader *node, void * data);
		void visit(ASTvoidType *node, void * data);
		void visit(ASTpommeConstructor *node, void * data);
		void visit(ASTpommeDestructor *node, void * data);
		void visit(ASTpommeAnd *node, void * data);
		void visit(ASTpommeOr *node, void * data);
		void visit(ASTpommeEQ *node, void * data);
		void visit(ASTpommeNEQ *node, void * data);
		void visit(ASTpommeGT *node, void * data);
		void visit(ASTpommeGET *node, void * data);
		void visit(ASTpommeLT *node, void * data);
		void visit(ASTpommeLET *node, void * data);
		void visit(ASTpommeAdd *node, void * data);
		void visit(ASTpommeMinus *node, void * data);
		void visit(ASTpommeShiftR *node, void * data);
		void visit(ASTpommeShiftL *node, void * data);
		void visit(ASTpommeMult *node, void * data);
		void visit(ASTpommeDiv *node, void * data);
		void visit(ASTpommeModulo *node, void * data);
		void visit(ASTpommeUnary *node, void * data);
		void visit(ASTpommeNot *node, void * data);
		void visit(ASTpommeTilde *node, void * data);
		void visit(ASTpommeNew *node, void * data);
		void visit(ASTpommeTrue *node, void * data);
		void visit(ASTpommeFalse *node, void * data);
		void visit(ASTpommeNull *node, void * data);
		void visit(ASTlistacces *node, void * data);
		void visit(ASTlistaccesP *node, void * data);
		void visit(ASTacnil *node, void * data);
		void visit(ASTaccessMethode *node, void * data);

	private:

		void emitByte(uint8_t byte);
		void emitBytes(uint8_t byte1, uint8_t byte2);
		void emit16Bits(uint16_t val);

		void emitReturn();

		int emitJump(uint8_t instruction);
		void patchJump(int offset);

		void emitLoop(int loopStart);

		void emitDefaultValue(const std::string& typeName);

		void endCompiler();
		void emitConstant(Value value);
		uint8_t makeConstant(Value value);

		void beginScope();
		void endScope();

		void access(Node* left, Node* middle, Node* right, void * data);
		void method(SimpleNode *node, ASTident* name, uint16_t index, bool constructor);

		int addLocal(const std::string& name);
		void namedVariable(const std::string& name, bool assign);
	private:
		ObjFunction* function;
		int line;

		std::array<Local, UINT8_COUNT> locals;
  		int localCount;

		int scopeDepth;

		bool m_InClass;
		bool m_InMethod;
	};
}