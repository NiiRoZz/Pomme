/* Generated By:JJTree: Do not edit this line. ASTheaders.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTheaders.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTheaders::ASTheaders(int id) : PommeNode(id) {
  }
  ASTheaders::ASTheaders(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTheaders::~ASTheaders() {
  }

  /** Accept the visitor. **/
  void  ASTheaders::jjtAccept(PommeLexerVisitor *visitor, void * data) const {
    return 
    visitor->visit(this, data);
  }

}
