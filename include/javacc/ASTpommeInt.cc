/* Generated By:JJTree: Do not edit this line. ASTpommeInt.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeInt.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeInt::ASTpommeInt(int id) : PommeNode(id) {
  }
  ASTpommeInt::ASTpommeInt(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeInt::~ASTpommeInt() {
  }

  /** Accept the visitor. **/
  void  ASTpommeInt::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}