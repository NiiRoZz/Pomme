/* Generated By:JJTree: Do not edit this line. ASTpommeOr.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeOr.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeOr::ASTpommeOr(int id) : PommeNode(id) {
  }
  ASTpommeOr::ASTpommeOr(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeOr::~ASTpommeOr() {
  }

  /** Accept the visitor. **/
  void  ASTpommeOr::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}