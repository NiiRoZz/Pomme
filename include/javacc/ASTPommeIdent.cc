/* Generated By:JJTree: Do not edit this line. ASTPommeIdent.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeIdent.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeIdent::ASTPommeIdent(int id) : PommeNode(id) {
  }
  ASTPommeIdent::ASTPommeIdent(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeIdent::~ASTPommeIdent() {
  }

  /** Accept the visitor. **/
  void  ASTPommeIdent::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
