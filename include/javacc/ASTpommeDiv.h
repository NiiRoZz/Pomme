/* Generated By:JJTree: Do not edit this line. ASTpommeDiv.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeDiv_H_
#define ASTpommeDiv_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeDiv : public PommeNode {
public: 
           ASTpommeDiv(int id);
           ASTpommeDiv(PommeLexer *parser, int id);
  virtual ~ASTpommeDiv();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
