/* Generated By:JJTree: Do not edit this line. ASTPommeNEQ.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeNEQ_H_
#define ASTPommeNEQ_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeNEQ : public PommeNode {
public: 
           ASTPommeNEQ(int id);
           ASTPommeNEQ(PommeLexer *parser, int id);
  virtual ~ASTPommeNEQ();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif