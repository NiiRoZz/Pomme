/* Generated By:JJTree: Do not edit this line. ASTPommeAccessMethode.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTPommeAccessMethode.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTPommeAccessMethode::ASTPommeAccessMethode(int id) : PommeNode(id) {
  }
  ASTPommeAccessMethode::ASTPommeAccessMethode(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTPommeAccessMethode::~ASTPommeAccessMethode() {
  }

  /** Accept the visitor. **/
  void  ASTPommeAccessMethode::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}