/* Generated By:JJTree: Do not edit this line. ASTandeq.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTandeq.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTandeq::ASTandeq(int id) : PommeNode(id) {
  }
  ASTandeq::ASTandeq(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTandeq::~ASTandeq() {
  }

  /** Accept the visitor. **/
  void  ASTandeq::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
