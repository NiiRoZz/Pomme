/* Generated By:JJTree: Do not edit this line. ASTscinil.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTscinil.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTscinil::ASTscinil(int id) : PommeNode(id) {
  }
  ASTscinil::ASTscinil(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTscinil::~ASTscinil() {
  }

  /** Accept the visitor. **/
  void  ASTscinil::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
