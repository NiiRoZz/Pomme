/* Generated By:JJTree: Do not edit this line. ASTvoidType.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTvoidType.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTvoidType::ASTvoidType(int id) : PommeNode(id) {
  }
  ASTvoidType::ASTvoidType(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTvoidType::~ASTvoidType() {
  }

  /** Accept the visitor. **/
  void  ASTvoidType::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
