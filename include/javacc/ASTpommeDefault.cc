/* Generated By:JJTree: Do not edit this line. ASTpommeDefault.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeDefault.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeDefault::ASTpommeDefault(int id) : PommeNode(id) {
  }
  ASTpommeDefault::ASTpommeDefault(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeDefault::~ASTpommeDefault() {
  }

  /** Accept the visitor. **/
  void  ASTpommeDefault::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
