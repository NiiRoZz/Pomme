/* Generated By:JJTree: Do not edit this line. ASTpommeMinus.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeMinus.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeMinus::ASTpommeMinus(int id) : PommeNode(id) {
  }
  ASTpommeMinus::ASTpommeMinus(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeMinus::~ASTpommeMinus() {
  }

  /** Accept the visitor. **/
  void  ASTpommeMinus::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}