/* Generated By:JJTree: Do not edit this line. ASTPommeLET.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeLET.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeLET::ASTPommeLET(int id) : PommeNode(id) {
  }
  ASTPommeLET::ASTPommeLET(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeLET::~ASTPommeLET() {
  }

  /** Accept the visitor. **/
  void  ASTPommeLET::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
