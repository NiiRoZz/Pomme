/* Generated By:JJTree: Do not edit this line. ASTpommeGlobalFunction.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeGlobalFunction.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeGlobalFunction::ASTpommeGlobalFunction(int id) : PommeNode(id) {
  }
  ASTpommeGlobalFunction::ASTpommeGlobalFunction(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeGlobalFunction::~ASTpommeGlobalFunction() {
  }

  /** Accept the visitor. **/
  void  ASTpommeGlobalFunction::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
