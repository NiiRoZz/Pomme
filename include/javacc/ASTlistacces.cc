/* Generated By:JJTree: Do not edit this line. ASTlistacces.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTlistacces.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTlistacces::ASTlistacces(int id) : PommeNode(id) {
  }
  ASTlistacces::ASTlistacces(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTlistacces::~ASTlistacces() {
  }

  /** Accept the visitor. **/
  void  ASTlistacces::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}