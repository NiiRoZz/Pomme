/* Generated By:JJTree: Do not edit this line. ASTpommeWhile.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeWhile.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeWhile::ASTpommeWhile(int id) : PommeNode(id) {
  }
  ASTpommeWhile::ASTpommeWhile(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeWhile::~ASTpommeWhile() {
  }

  /** Accept the visitor. **/
  void  ASTpommeWhile::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}