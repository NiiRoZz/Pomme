/* Generated By:JJTree: Do not edit this line. ASTdecls.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTdecls.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTdecls::ASTdecls(int id) : PommeNode(id) {
  }
  ASTdecls::ASTdecls(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTdecls::~ASTdecls() {
  }

  /** Accept the visitor. **/
  void  ASTdecls::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
