/* Generated By:JJTree: Do not edit this line. ASTPommeDestructor.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeDestructor.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeDestructor::ASTPommeDestructor(int id) : PommeNode(id) {
  }
  ASTPommeDestructor::ASTPommeDestructor(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeDestructor::~ASTPommeDestructor() {
  }

  /** Accept the visitor. **/
  void  ASTPommeDestructor::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}