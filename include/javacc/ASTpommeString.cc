/* Generated By:JJTree: Do not edit this line. ASTpommeString.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeString.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeString::ASTpommeString(int id) : PommeNode(id) {
  }
  ASTpommeString::ASTpommeString(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeString::~ASTpommeString() {
  }

  /** Accept the visitor. **/
  void  ASTpommeString::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}