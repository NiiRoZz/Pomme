/* Generated By:JJTree: Do not edit this line. ASTPommeIncrPre.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeIncrPre.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeIncrPre::ASTPommeIncrPre(int id) : PommeNode(id) {
  }
  ASTPommeIncrPre::ASTPommeIncrPre(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeIncrPre::~ASTPommeIncrPre() {
  }

  /** Accept the visitor. **/
  void  ASTPommeIncrPre::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}