/* Generated By:JJTree: Do not edit this line. ASTPommeShiftREq.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeShiftREq_H_
#define ASTPommeShiftREq_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeShiftREq : public PommeNode {
public: 
           ASTPommeShiftREq(int id);
           ASTPommeShiftREq(PommeLexer *parser, int id);
  virtual ~ASTPommeShiftREq();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif