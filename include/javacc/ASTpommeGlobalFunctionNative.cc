/* Generated By:JJTree: Do not edit this line. ASTpommeGlobalFunctionNative.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeGlobalFunctionNative.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeGlobalFunctionNative::ASTpommeGlobalFunctionNative(int id) : PommeNode(id) {
  }
  ASTpommeGlobalFunctionNative::ASTpommeGlobalFunctionNative(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeGlobalFunctionNative::~ASTpommeGlobalFunctionNative() {
  }

  /** Accept the visitor. **/
  void  ASTpommeGlobalFunctionNative::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
