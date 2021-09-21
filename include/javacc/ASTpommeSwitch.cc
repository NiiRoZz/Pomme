/* Generated By:JJTree: Do not edit this line. ASTpommeSwitch.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeSwitch.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeSwitch::ASTpommeSwitch(int id) : PommeNode(id) {
  }
  ASTpommeSwitch::ASTpommeSwitch(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeSwitch::~ASTpommeSwitch() {
  }

  /** Accept the visitor. **/
  void  ASTpommeSwitch::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
