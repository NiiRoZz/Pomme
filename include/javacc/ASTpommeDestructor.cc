/* Generated By:JJTree: Do not edit this line. ASTpommeDestructor.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeDestructor.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeDestructor::ASTpommeDestructor(int id) : PommeNode(id) {
  }
  ASTpommeDestructor::ASTpommeDestructor(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeDestructor::~ASTpommeDestructor() {
  }

  /** Accept the visitor. **/
  void  ASTpommeDestructor::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}