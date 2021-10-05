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
		void visit(const SimpleNode *node, void * data);
		void visit(const ASTinput *node, void * data);
		void visit(const ASTident *node, void * data);
		void visit(const ASTidentOp *node, void * data);
		void visit(const ASTpommeInt *node, void * data);
		void visit(const ASTpommeFloat *node, void * data);
		void visit(const ASTpommeString *node, void * data);
		void visit(const ASTscopes *node, void * data);
		void visit(const ASTscinil *node, void * data);
		void visit(const ASTpommeTypeDef *node, void * data);
		void visit(const ASTpommeClass *node, void * data);
		void visit(const ASTpommeClassChild *node, void * data);
		void visit(const ASTpommeModdedClass *node, void * data);
		void visit(const ASTdecls *node, void * data);
		void visit(const ASTdnil *node, void * data);
		void visit(const ASTpommeMethode *node, void * data);
		void visit(const ASTpommeMethodeNative *node, void * data);
		void visit(const ASTidentFuncs *node, void * data);
		void visit(const ASTpommeStatic *node, void * data);
		void visit(const ASTsnil *node, void * data);
		void visit(const ASTpommePublic *node, void * data);
		void visit(const ASTpommePrivate *node, void * data);
		void visit(const ASTpommeProtected *node, void * data);
		void visit(const ASTvinil *node, void * data);
		void visit(const ASTpommeOverride *node, void * data);
		void visit(const ASTonil *node, void * data);
		void visit(const ASTpommeEnum *node, void * data);
		void visit(const ASTpommeExtendsEnum *node, void * data);
		void visit(const ASTpommeModdedEnum *node, void * data);
		void visit(const ASTdeclenums *node, void * data);
		void visit(const ASTennil *node, void * data);
		void visit(const ASTenumassign *node, void * data);
		void visit(const ASTenumdefault *node, void * data);
		void visit(const ASTpommeGlobalFunction *node, void * data);
		void visit(const ASTpommeGlobalFunctionNative *node, void * data);
		void visit(const ASTinstrs *node, void * data);
		void visit(const ASTinil *node, void * data);
		void visit(const ASTincrementPre *node, void * data);
		void visit(const ASTdecrementPre *node, void * data);
		void visit(const ASTpommeReturn *node, void * data);
		void visit(const ASTpommeWhile *node, void * data);
		void visit(const ASTpommeBreak *node, void * data);
		void visit(const ASTpommeIf *node, void * data);
		void visit(const ASTpommePrint *node, void * data);
		void visit(const ASTpommeSwitch *node, void * data);
		void visit(const ASTassignement *node, void * data);
		void visit(const ASTaddeq *node, void * data);
		void visit(const ASTminuseq *node, void * data);
		void visit(const ASTdiveq *node, void * data);
		void visit(const ASTmulteq *node, void * data);
		void visit(const ASToreq *node, void * data);
		void visit(const ASTandeq *node, void * data);
		void visit(const ASTshiftleq *node, void * data);
		void visit(const ASTshiftreq *node, void * data);
		void visit(const ASTincrementPost *node, void * data);
		void visit(const ASTdecrementPost *node, void * data);
		void visit(const ASTpommeCases *node, void * data);
		void visit(const ASTpommeDefault *node, void * data);
		void visit(const ASTswinil *node, void * data);
		void visit(const ASTpommeCase *node, void * data);
		void visit(const ASTlistexp *node, void * data);
		void visit(const ASTexnil *node, void * data);
		void visit(const ASTpommeVariable *node, void * data);
		void visit(const ASTpommeConstant *node, void * data);
		void visit(const ASTpommeArray *node, void * data);
		void visit(const ASTomega *node, void * data);
		void visit(const ASTheaders *node, void * data);
		void visit(const ASTenil *node, void * data);
		void visit(const ASTheader *node, void * data);
		void visit(const ASTvoidType *node, void * data);
		void visit(const ASTpommeDestructor *node, void * data);
		void visit(const ASTpommeAnd *node, void * data);
		void visit(const ASTpommeOr *node, void * data);
		void visit(const ASTpommeEQ *node, void * data);
		void visit(const ASTpommeNEQ *node, void * data);
		void visit(const ASTpommeGT *node, void * data);
		void visit(const ASTpommeGET *node, void * data);
		void visit(const ASTpommeLT *node, void * data);
		void visit(const ASTpommeLET *node, void * data);
		void visit(const ASTpommeAdd *node, void * data);
		void visit(const ASTpommeMinus *node, void * data);
		void visit(const ASTpommeShiftR *node, void * data);
		void visit(const ASTpommeShiftL *node, void * data);
		void visit(const ASTpommeMult *node, void * data);
		void visit(const ASTpommeDiv *node, void * data);
		void visit(const ASTpommeModulo *node, void * data);
		void visit(const ASTpommeUnary *node, void * data);
		void visit(const ASTpommeNot *node, void * data);
		void visit(const ASTpommeTilde *node, void * data);
		void visit(const ASTpommeNew *node, void * data);
		void visit(const ASTpommeTrue *node, void * data);
		void visit(const ASTpommeFalse *node, void * data);
		void visit(const ASTpommeNull *node, void * data);
		void visit(const ASTlistacces *node, void * data);
		void visit(const ASTacnil *node, void * data);
		void visit(const ASTaccessTab *node, void * data);
		void visit(const ASTaccessMethode *node, void * data);

	private:
		void emitBytes(uint8_t byte1, uint8_t byte2);
		void emitByte(uint8_t byte);
		void emitReturn();
		void endCompiler();
		void emitConstant(Value value);
		uint8_t makeConstant(Value value);

		void beginScope();
		void endScope();

		int addLocal(const std::string& name);
	private:
		ObjFunction* function;
		int line;

		std::array<Local, UINT8_COUNT> locals;
  		int localCount;

		int scopeDepth;
	};
}