/* Generated By:JJTree: Do not edit this line. ASTPommeMult.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeMult.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeMult::ASTPommeMult(int id) : PommeNode(id) {
  }
  ASTPommeMult::ASTPommeMult(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeMult::~ASTPommeMult() {
  }

  /** Accept the visitor. **/
  void  ASTPommeMult::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
