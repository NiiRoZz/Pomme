/* Generated By:JJTree: Do not edit this line. ASTPommeScopes.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeScopes.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeScopes::ASTPommeScopes(int id) : PommeNode(id) {
  }
  ASTPommeScopes::ASTPommeScopes(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeScopes::~ASTPommeScopes() {
  }

  /** Accept the visitor. **/
  void  ASTPommeScopes::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}