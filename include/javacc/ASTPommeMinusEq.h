/* Generated By:JJTree: Do not edit this line. ASTPommeMinusEq.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeMinusEq_H_
#define ASTPommeMinusEq_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeMinusEq : public PommeNode {
public: 
           ASTPommeMinusEq(int id);
           ASTPommeMinusEq(PommeLexer *parser, int id);
  virtual ~ASTPommeMinusEq();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif
