/* Generated By:JJTree: Do not edit this line. ASTPommePrint.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommePrint.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommePrint::ASTPommePrint(int id) : PommeNode(id) {
  }
  ASTPommePrint::ASTPommePrint(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommePrint::~ASTPommePrint() {
  }

  /** Accept the visitor. **/
  void  ASTPommePrint::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
