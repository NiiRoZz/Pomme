#include "CompilerVisitor.h"
#include "VM/VirtualMachine.h"
#include "VM/Chunk.h"

#include <iostream>

namespace Pomme
{
	CompilerVisitor::CompilerVisitor(VirtualMachine& vm)
	: m_Vm(vm)
	{
	}

  Chunk* CompilerVisitor::currentChunk() {
		return this->compilingChunk;
	}

  void CompilerVisitor::emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
  }

	void CompilerVisitor::emitByte(uint8_t byte) {
		currentChunk()->writeChunk(byte, line);
	}

	void CompilerVisitor::endCompiler() {
		emitReturn();
	}

	void CompilerVisitor::emitReturn() {
		emitByte(AS_OPCODE(OpCode::OP_RETURN));
	}

  void CompilerVisitor::emitConstant(Value value) {
    emitBytes(AS_OPCODE(OpCode::OP_CONSTANT), makeConstant(value));
  }

  uint8_t CompilerVisitor::makeConstant(Value value) {
    int constant = currentChunk()->addConstant(value);
    if (constant > UINT8_MAX) {
      //std::error("Too many constants in one chunk.");
      return 0;
    }

    return (uint8_t)constant;
  }

	void CompilerVisitor::visit(const SimpleNode *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTinput *node, void * data) 
  {
    std::cout << "ASTinput " << node->jjtGetNumChildren() << std::endl;

    node->jjtChildrenAccept(this, data);
  }

  void CompilerVisitor::visit(const ASTident *node, void * data) 
  {
    std::cout << "ASTident : " << node->m_Identifier << std::endl;
  }

  void CompilerVisitor::visit(const ASTidentOp *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeInt *node, void * data) 
  {
    std::cout << "ASTpommeInt : " << node->m_Value << std::endl;
  }

  void CompilerVisitor::visit(const ASTpommeFloat *node, void * data) 
  {
    std::cout << "ASTpommeFloat : " << node->m_Value << std::endl;
  }

  void CompilerVisitor::visit(const ASTpommeString *node, void * data) 
  {
    std::cout << "ASTpommeString : " << node->m_Value << std::endl;
  }

  void CompilerVisitor::visit(const ASTscopes *node, void * data) 
  {
    std::cout << "ASTscopes " << node->jjtGetNumChildren() << std::endl;

    node->jjtChildrenAccept(this, data);
  }

  void CompilerVisitor::visit(const ASTscinil *node, void * data) 
  {
    std::cout << "ASTscinil " << node->jjtGetNumChildren() << std::endl;
  }

  /*void CompilerVisitor::visit(const ASTdefaultClass *node, void * data) 
  {
    std::cout << "ASTdefaultClass " << node->jjtGetNumChildren() << std::endl;

    node->jjtChildrenAccept(this, data);
  }

  void CompilerVisitor::visit(const ASTclassChild *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTmoddedClass *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTdecls *node, void * data) 
  {
    std::cout << "ASTdecls " << node->jjtGetNumChildren() << std::endl;

    node->jjtChildrenAccept(this, data);
  }

  void CompilerVisitor::visit(const ASTdnil *node, void * data) 
  {
    std::cout << "ASTdnil " << node->jjtGetNumChildren() << std::endl;
  }

  /*void CompilerVisitor::visit(const ASTmethode *node, void * data) 
  {
    std::cout << "ASTmethode " << node->jjtGetNumChildren() << std::endl;

    node->jjtChildrenAccept(this, data);
  }

  void CompilerVisitor::visit(const ASTmethodeNative *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTidentFuncs *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTstaticChild *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTsnil *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTpublicChild *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTprivateChild *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTprotectedChild *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTvinil *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASToverrideChild *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTonil *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTenumerate *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTextendsEnumerate *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTmoddedEnumerate *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTdeclenums *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTennil *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTenumassign *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTenumdefault *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTglobalFunction *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTglobalFunctionNative *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTinstrs *node, void * data) 
  {
    std::cout << "ASTinstrs " << node->jjtGetNumChildren() << std::endl;

    node->jjtChildrenAccept(this, data);
  }

  void CompilerVisitor::visit(const ASTinil *node, void * data) 
  {
    std::cout << "ASTinil " << node->jjtGetNumChildren() << std::endl;
  }

  /*void CompilerVisitor::visit(const ASTcallI *node, void * data) 
  {

  }*/

  /*void CompilerVisitor::visit(const ASTcallIClass *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTassignement *node, void * data) 
  {
    emitByte(AS_OPCODE(OpCode::OP_ASSIGN));
  }

  void CompilerVisitor::visit(const ASTaddeq *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_ADD_EQ));
  }

  void CompilerVisitor::visit(const ASTminuseq *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_SUBTRACT_EQ));
  }

  void CompilerVisitor::visit(const ASTdiveq *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_DIVIDE_EQ));
  }

  void CompilerVisitor::visit(const ASTmulteq *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_MULTIPLY_EQ));
  }

  void CompilerVisitor::visit(const ASToreq *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_OR_EQ));
  }

  void CompilerVisitor::visit(const ASTandeq *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_AND_EQ));
  }

  void CompilerVisitor::visit(const ASTshiftleq *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_SHIFTL_EQ));
  }

  void CompilerVisitor::visit(const ASTshiftreq *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_SHIFTR_EQ));
  }

  void CompilerVisitor::visit(const ASTincrementPost *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_INCR_POST));
  }

  void CompilerVisitor::visit(const ASTdecrementPost *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_DECR_POST));
  }

  void CompilerVisitor::visit(const ASTincrementPre *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_INCR_PRE));
  }

  void CompilerVisitor::visit(const ASTdecrementPre *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_DECR_PRE));
  }

  void CompilerVisitor::visit(const ASTpommeReturn *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_RETURN));
  }

  void CompilerVisitor::visit(const ASTpommeWhile *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeBreak *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeIf *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommePrint *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_PRINT));
  }

  void CompilerVisitor::visit(const ASTpommeSwitch *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeCases *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeDefault *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTswinil *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTlistexp *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTexnil *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTvar *node, void * data) 
  {
    std::cout << "ASTvar " << node->jjtGetNumChildren() << std::endl;

    node->jjtChildrenAccept(this, data);
  }

  void CompilerVisitor::visit(const ASTconstant *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTarray *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTomega *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTentetes *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTenil *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTentete *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTvoidType *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTidentDestructor *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTpommeAnd *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_AND));
  }

  void CompilerVisitor::visit(const ASTpommeOr *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_OR));
  }

  void CompilerVisitor::visit(const ASTpommeEQ *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_EQ));
  }

  void CompilerVisitor::visit(const ASTpommeNEQ *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_NEQ));
  }

  void CompilerVisitor::visit(const ASTpommeGT *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_GT));
  }

  void CompilerVisitor::visit(const ASTpommeGET *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_GET));
  }

  void CompilerVisitor::visit(const ASTpommeLT *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_LT));
  }

  void CompilerVisitor::visit(const ASTpommeLET *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_LET));
  }

  void CompilerVisitor::visit(const ASTpommeAdd *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_ADD));
  }

  void CompilerVisitor::visit(const ASTpommeMinus *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_SUBTRACT));
  }

  void CompilerVisitor::visit(const ASTpommeShiftR *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_SHIFTR));
  }

  void CompilerVisitor::visit(const ASTpommeShiftL *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_SHIFTL));
  }

  void CompilerVisitor::visit(const ASTpommeMult *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_MULTIPLY));
  }

  void CompilerVisitor::visit(const ASTpommeDiv *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_DIVIDE));
  }

  void CompilerVisitor::visit(const ASTpommeModulo *node, void * data) 
  {
    node->jjtChildrenAccept(this, data);
    emitByte(AS_OPCODE(OpCode::OP_MODULO));
  }

  void CompilerVisitor::visit(const ASTpommeUnary *node, void * data) 
  {
    emitByte(AS_OPCODE(OpCode::OP_NEGATE));
  }

  void CompilerVisitor::visit(const ASTpommeNot *node, void * data) 
  {
    emitByte(AS_OPCODE(OpCode::OP_NOT));
  }

  void CompilerVisitor::visit(const ASTpommeTilde *node, void * data) 
  {
    emitByte(AS_OPCODE(OpCode::OP_TILDE));
  }

  /*void CompilerVisitor::visit(const ASTcallE *node, void * data) 
  {

  }*/

  /*void CompilerVisitor::visit(const ASTcallEClass *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTpommeNew *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeTrue *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeFalse *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeNull *node, void * data) 
  {

  }

  /*void CompilerVisitor::visit(const ASTaccessMember *node, void * data) 
  {

  }*/

  void CompilerVisitor::visit(const ASTaccessTab *node, void * data) 
  {

  }

}