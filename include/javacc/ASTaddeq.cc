/* Generated By:JJTree: Do not edit this line. ASTaddeq.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTaddeq.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTaddeq::ASTaddeq(int id) : PommeNode(id) {
  }
  ASTaddeq::ASTaddeq(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTaddeq::~ASTaddeq() {
  }

  /** Accept the visitor. **/
  void  ASTaddeq::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}