#include "CompilerVisitor.h"
#include "VM/VirtualMachine.h"

#include <iostream>

namespace Pomme
{
	CompilerVisitor::CompilerVisitor(VirtualMachine& vm)
	: m_Vm(vm)
	{
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

  }

  void CompilerVisitor::visit(const ASTaddeq *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTminuseq *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTdiveq *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTmulteq *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASToreq *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTandeq *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTshiftleq *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTshiftreq *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTincrementPost *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTdecrementPost *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTincrementPre *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTdecrementPre *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeReturn *node, void * data) 
  {

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

  }

  void CompilerVisitor::visit(const ASTpommeOr *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeEQ *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeNEQ *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeGT *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeGET *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeLT *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeLET *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeAdd *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeMinus *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeShiftR *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeShiftL *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeMult *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeDiv *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeModulo *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeUnary *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeNot *node, void * data) 
  {

  }

  void CompilerVisitor::visit(const ASTpommeTilde *node, void * data) 
  {

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