/* Generated By:JJTree: Do not edit this line. ASTPommeShiftR.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeShiftR.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeShiftR::ASTPommeShiftR(int id) : PommeNode(id) {
  }
  ASTPommeShiftR::ASTPommeShiftR(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeShiftR::~ASTPommeShiftR() {
  }

  /** Accept the visitor. **/
  void  ASTPommeShiftR::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}