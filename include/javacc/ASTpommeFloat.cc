/* Generated By:JJTree: Do not edit this line. ASTpommeFloat.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeFloat.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeFloat::ASTpommeFloat(int id) : PommeNode(id) {
  }
  ASTpommeFloat::ASTpommeFloat(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeFloat::~ASTpommeFloat() {
  }

  /** Accept the visitor. **/
  void  ASTpommeFloat::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
