/* Generated By:JJTree: Do not edit this line. ASTinstrs.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTinstrs.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTinstrs::ASTinstrs(int id) : PommeNode(id) {
  }
  ASTinstrs::ASTinstrs(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTinstrs::~ASTinstrs() {
  }

  /** Accept the visitor. **/
  void  ASTinstrs::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
