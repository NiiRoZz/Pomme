/* Generated By:JJTree: Do not edit this line. ASTinil.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTinil.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTinil::ASTinil(int id) : PommeNode(id) {
  }
  ASTinil::ASTinil(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTinil::~ASTinil() {
  }

  /** Accept the visitor. **/
  void  ASTinil::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
