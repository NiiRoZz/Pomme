/* Generated By:JJTree: Do not edit this line. ASTpommeNEQ.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeNEQ_H_
#define ASTpommeNEQ_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeNEQ : public PommeNode {
public: 
           ASTpommeNEQ(int id);
           ASTpommeNEQ(PommeLexer *parser, int id);
  virtual ~ASTpommeNEQ();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
};

}

#endif
