/* Generated By:JJTree: Do not edit this line. ASTscopes.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTscopes.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTscopes::ASTscopes(int id) : PommeNode(id) {
  }
  ASTscopes::ASTscopes(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTscopes::~ASTscopes() {
  }

  /** Accept the visitor. **/
  void  ASTscopes::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
