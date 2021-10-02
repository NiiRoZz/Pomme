#pragma once

#include "PommeLexerVisitor.h"
#include "VM/Chunk.h"

namespace Pomme
{
	class VirtualMachine;

	class CompilerVisitor : public PommeLexerVisitor
	{
		VirtualMachine& m_Vm;

	public:
		CompilerVisitor(VirtualMachine &vm);
		Chunk* compilingChunk;

		int line;

		Chunk* currentChunk();
		void emitBytes(uint8_t byte1, uint8_t byte2);
		void emitByte(uint8_t byte);
		void emitReturn();
		void endCompiler();
		void emitConstant(Value value);
		uint8_t makeConstant(Value value);

	public:
		// Inherited via TestLexerVisitor
		virtual void visit(const SimpleNode *node, void * data) override;
		virtual void visit(const ASTinput *node, void * data) override;
		virtual void visit(const ASTident *node, void * data) override;
		virtual void visit(const ASTidentOp *node, void * data) override;
		virtual void visit(const ASTpommeInt *node, void * data) override;
		virtual void visit(const ASTpommeFloat *node, void * data) override;
		virtual void visit(const ASTpommeString *node, void * data) override;
		virtual void visit(const ASTscopes *node, void * data) override;
		virtual void visit(const ASTscinil *node, void * data) override;
		//virtual void visit(const ASTdefaultClass *node, void * data) override;
		//virtual void visit(const ASTclassChild *node, void * data) override;
		//virtual void visit(const ASTmoddedClass *node, void * data) override;
		virtual void visit(const ASTdecls *node, void * data) override;
		virtual void visit(const ASTdnil *node, void * data) override;
		//virtual void visit(const ASTmethode *node, void * data) override;
		//virtual void visit(const ASTmethodeNative *node, void * data) override;
		virtual void visit(const ASTidentFuncs *node, void * data) override;
		//virtual void visit(const ASTstaticChild *node, void * data) override;
		virtual void visit(const ASTsnil *node, void * data) override;
		//virtual void visit(const ASTpublicChild *node, void * data) override;
		//virtual void visit(const ASTprivateChild *node, void * data) override;
		//virtual void visit(const ASTprotectedChild *node, void * data) override;
		virtual void visit(const ASTvinil *node, void * data) override;
		//virtual void visit(const ASToverrideChild *node, void * data) override;
		virtual void visit(const ASTonil *node, void * data) override;
		//virtual void visit(const ASTenumerate *node, void * data) override;
		//virtual void visit(const ASTextendsEnumerate *node, void * data) override;
		//virtual void visit(const ASTmoddedEnumerate *node, void * data) override;
		virtual void visit(const ASTdeclenums *node, void * data) override;
		virtual void visit(const ASTennil *node, void * data) override;
		virtual void visit(const ASTenumassign *node, void * data) override;
		virtual void visit(const ASTenumdefault *node, void * data) override;
		//virtual void visit(const ASTglobalFunction *node, void * data) override;
		//virtual void visit(const ASTglobalFunctionNative *node, void * data) override;
		virtual void visit(const ASTinstrs *node, void * data) override;
		virtual void visit(const ASTinil *node, void * data) override;
		//virtual void visit(const ASTcallI *node, void * data) override;
		//virtual void visit(const ASTcallIClass *node, void * data) override;
		virtual void visit(const ASTassignement *node, void * data) override;
		virtual void visit(const ASTaddeq *node, void * data) override;
		virtual void visit(const ASTminuseq *node, void * data) override;
		virtual void visit(const ASTdiveq *node, void * data) override;
		virtual void visit(const ASTmulteq *node, void * data) override;
		virtual void visit(const ASToreq *node, void * data) override;
		virtual void visit(const ASTandeq *node, void * data) override;
		virtual void visit(const ASTshiftleq *node, void * data) override;
		virtual void visit(const ASTshiftreq *node, void * data) override;
		virtual void visit(const ASTincrementPost *node, void * data) override;
		virtual void visit(const ASTdecrementPost *node, void * data) override;
		virtual void visit(const ASTincrementPre *node, void * data) override;
		virtual void visit(const ASTdecrementPre *node, void * data) override;
		virtual void visit(const ASTpommeReturn *node, void * data) override;
		virtual void visit(const ASTpommeWhile *node, void * data) override;
		virtual void visit(const ASTpommeBreak *node, void * data) override;
		virtual void visit(const ASTpommeIf *node, void * data) override;
		virtual void visit(const ASTpommePrint *node, void * data) override;
		virtual void visit(const ASTpommeSwitch *node, void * data) override;
		virtual void visit(const ASTpommeCases *node, void * data) override;
		virtual void visit(const ASTpommeDefault *node, void * data) override;
		virtual void visit(const ASTswinil *node, void * data) override;
		virtual void visit(const ASTlistexp *node, void * data) override;
		virtual void visit(const ASTexnil *node, void * data) override;
		//virtual void visit(const ASTvar *node, void * data) override;
		//virtual void visit(const ASTconstant *node, void * data) override;
		//virtual void visit(const ASTarray *node, void * data) override;
		virtual void visit(const ASTomega *node, void * data) override;
		//virtual void visit(const ASTentetes *node, void * data) override;
		virtual void visit(const ASTenil *node, void * data) override;
		//virtual void visit(const ASTentete *node, void * data) override;
		virtual void visit(const ASTvoidType *node, void * data) override;
		//virtual void visit(const ASTidentDestructor *node, void * data) override;
		virtual void visit(const ASTpommeAnd *node, void * data) override;
		virtual void visit(const ASTpommeOr *node, void * data) override;
		virtual void visit(const ASTpommeEQ *node, void * data) override;
		virtual void visit(const ASTpommeNEQ *node, void * data) override;
		virtual void visit(const ASTpommeGT *node, void * data) override;
		virtual void visit(const ASTpommeGET *node, void * data) override;
		virtual void visit(const ASTpommeLT *node, void * data) override;
		virtual void visit(const ASTpommeLET *node, void * data) override;
		virtual void visit(const ASTpommeAdd *node, void * data) override;
		virtual void visit(const ASTpommeMinus *node, void * data) override;
		virtual void visit(const ASTpommeShiftR *node, void * data) override;
		virtual void visit(const ASTpommeShiftL *node, void * data) override;
		virtual void visit(const ASTpommeMult *node, void * data) override;
		virtual void visit(const ASTpommeDiv *node, void * data) override;
		virtual void visit(const ASTpommeModulo *node, void * data) override;
		virtual void visit(const ASTpommeUnary *node, void * data) override;
		virtual void visit(const ASTpommeNot *node, void * data) override;
		virtual void visit(const ASTpommeTilde *node, void * data) override;
		//virtual void visit(const ASTcallE *node, void * data) override;
		//virtual void visit(const ASTcallEClass *node, void * data) override;
		virtual void visit(const ASTpommeNew *node, void * data) override;
		virtual void visit(const ASTpommeTrue *node, void * data) override;
		virtual void visit(const ASTpommeFalse *node, void * data) override;
		virtual void visit(const ASTpommeNull *node, void * data) override;
		//virtual void visit(const ASTaccessMember *node, void * data) override;
		virtual void visit(const ASTaccessTab *node, void * data) override;
	};
}