/* Generated By:JJTree: Do not edit this line. ASTPommeGlobalFunction.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeGlobalFunction.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeGlobalFunction::ASTPommeGlobalFunction(int id) : PommeNode(id) {
  }
  ASTPommeGlobalFunction::ASTPommeGlobalFunction(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeGlobalFunction::~ASTPommeGlobalFunction() {
  }

  /** Accept the visitor. **/
  void  ASTPommeGlobalFunction::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}