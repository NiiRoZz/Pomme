/* Generated By:JJTree: Do not edit this line. ASTpommeMult.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeMult.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeMult::ASTpommeMult(int id) : PommeNode(id) {
  }
  ASTpommeMult::ASTpommeMult(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeMult::~ASTpommeMult() {
  }

  /** Accept the visitor. **/
  void  ASTpommeMult::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
