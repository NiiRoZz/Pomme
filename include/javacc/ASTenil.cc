/* Generated By:JJTree: Do not edit this line. ASTenil.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTenil.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTenil::ASTenil(int id) : PommeNode(id) {
  }
  ASTenil::ASTenil(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTenil::~ASTenil() {
  }

  /** Accept the visitor. **/
  void  ASTenil::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
