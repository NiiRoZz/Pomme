/* Generated By:JJTree: Do not edit this line. ASTPommeVariable.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeVariable.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeVariable::ASTPommeVariable(int id) : PommeNode(id) {
  }
  ASTPommeVariable::ASTPommeVariable(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeVariable::~ASTPommeVariable() {
  }

  /** Accept the visitor. **/
  void  ASTPommeVariable::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}