/* Generated By:JJTree: Do not edit this line. ASTPommeEnnil.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeEnnil.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeEnnil::ASTPommeEnnil(int id) : PommeNode(id) {
  }
  ASTPommeEnnil::ASTPommeEnnil(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeEnnil::~ASTPommeEnnil() {
  }

  /** Accept the visitor. **/
  void  ASTPommeEnnil::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}