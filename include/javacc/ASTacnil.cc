/* Generated By:JJTree: Do not edit this line. ASTacnil.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTacnil.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTacnil::ASTacnil(int id) : PommeNode(id) {
  }
  ASTacnil::ASTacnil(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTacnil::~ASTacnil() {
  }

  /** Accept the visitor. **/
  void  ASTacnil::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
