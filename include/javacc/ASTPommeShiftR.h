/* Generated By:JJTree: Do not edit this line. ASTPommeShiftR.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeShiftR_H_
#define ASTPommeShiftR_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeShiftR : public PommeNode {
public: 
           ASTPommeShiftR(int id);
           ASTPommeShiftR(PommeLexer *parser, int id);
  virtual ~ASTPommeShiftR();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif