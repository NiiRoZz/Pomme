/* Generated By:JJTree: Do not edit this line. ASTenumdefault.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTenumdefault.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTenumdefault::ASTenumdefault(int id) : PommeNode(id) {
  }
  ASTenumdefault::ASTenumdefault(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTenumdefault::~ASTenumdefault() {
  }

  /** Accept the visitor. **/
  void  ASTenumdefault::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
