/* Generated By:JJTree: Do not edit this line. ASTpommeVariable.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeVariable.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeVariable::ASTpommeVariable(int id) : PommeNode(id) {
  }
  ASTpommeVariable::ASTpommeVariable(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeVariable::~ASTpommeVariable() {
  }

  /** Accept the visitor. **/
  void  ASTpommeVariable::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}