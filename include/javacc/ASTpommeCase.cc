/* Generated By:JJTree: Do not edit this line. ASTpommeCase.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeCase.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeCase::ASTpommeCase(int id) : PommeNode(id) {
  }
  ASTpommeCase::ASTpommeCase(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeCase::~ASTpommeCase() {
  }

  /** Accept the visitor. **/
  void  ASTpommeCase::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
