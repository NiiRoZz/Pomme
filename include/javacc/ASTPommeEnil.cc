/* Generated By:JJTree: Do not edit this line. ASTPommeEnil.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeEnil.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeEnil::ASTPommeEnil(int id) : PommeNode(id) {
  }
  ASTPommeEnil::ASTPommeEnil(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeEnil::~ASTPommeEnil() {
  }

  /** Accept the visitor. **/
  void  ASTPommeEnil::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}