/* Generated By:JJTree: Do not edit this line. ASTpommeModdedClass.cc Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#include "ASTpommeModdedClass.h"
#include "PommeLexerVisitor.h"

namespace Pomme {
  
  ASTpommeModdedClass::ASTpommeModdedClass(int id) : PommeNode(id) {
  }
  ASTpommeModdedClass::ASTpommeModdedClass(PommeLexer *parser, int id) : PommeNode(parser, id) {
  }
  ASTpommeModdedClass::~ASTpommeModdedClass() {
  }

  /** Accept the visitor. **/
  void  ASTpommeModdedClass::jjtAccept(PommeLexerVisitor *visitor, void * data) {
    return 
    visitor->visit(this, data);
  }

}
