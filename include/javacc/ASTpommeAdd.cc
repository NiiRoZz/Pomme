/* Generated By:JJTree: Do not edit this line. ASTpommeAdd.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeAdd.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeAdd::ASTpommeAdd(int id) : PommeNode(id) {
  }
  ASTpommeAdd::ASTpommeAdd(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeAdd::~ASTpommeAdd() {
  }

  /** Accept the visitor. **/
  void  ASTpommeAdd::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
