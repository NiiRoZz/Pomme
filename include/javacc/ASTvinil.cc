/* Generated By:JJTree: Do not edit this line. ASTvinil.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTvinil.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTvinil::ASTvinil(int id) : PommeNode(id) {
  }
  ASTvinil::ASTvinil(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTvinil::~ASTvinil() {
  }

  /** Accept the visitor. **/
  void  ASTvinil::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
