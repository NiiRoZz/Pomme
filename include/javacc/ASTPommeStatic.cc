/* Generated By:JJTree: Do not edit this line. ASTPommeStatic.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeStatic.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeStatic::ASTPommeStatic(int id) : PommeNode(id) {
  }
  ASTPommeStatic::ASTPommeStatic(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeStatic::~ASTPommeStatic() {
  }

  /** Accept the visitor. **/
  void  ASTPommeStatic::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
