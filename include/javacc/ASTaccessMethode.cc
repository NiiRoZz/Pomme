/* Generated By:JJTree: Do not edit this line. ASTaccessMethode.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTaccessMethode.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTaccessMethode::ASTaccessMethode(int id) : PommeNode(id) {
  }
  ASTaccessMethode::ASTaccessMethode(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTaccessMethode::~ASTaccessMethode() {
  }

  /** Accept the visitor. **/
  void  ASTaccessMethode::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
