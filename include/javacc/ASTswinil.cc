/* Generated By:JJTree: Do not edit this line. ASTswinil.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTswinil.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTswinil::ASTswinil(int id) : PommeNode(id) {
  }
  ASTswinil::ASTswinil(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTswinil::~ASTswinil() {
  }

  /** Accept the visitor. **/
  void  ASTswinil::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
