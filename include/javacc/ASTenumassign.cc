/* Generated By:JJTree: Do not edit this line. ASTenumassign.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTenumassign.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTenumassign::ASTenumassign(int id) : PommeNode(id) {
  }
  ASTenumassign::ASTenumassign(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTenumassign::~ASTenumassign() {
  }

  /** Accept the visitor. **/
  void  ASTenumassign::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
