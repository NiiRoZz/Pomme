/* Generated By:JJTree: Do not edit this line. ASTPommeLT.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeLT.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeLT::ASTPommeLT(int id) : PommeNode(id) {
  }
  ASTPommeLT::ASTPommeLT(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeLT::~ASTPommeLT() {
  }

  /** Accept the visitor. **/
  void  ASTPommeLT::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}