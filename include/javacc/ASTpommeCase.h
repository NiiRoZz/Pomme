/* Generated By:JJTree: Do not edit this line. ASTpommeCase.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeCase_H_
#define ASTpommeCase_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeCase : public PommeNode {
public: 
           ASTpommeCase(int id);
           ASTpommeCase(PommeLexer *parser, int id);
  virtual ~ASTpommeCase();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
