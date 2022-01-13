/* Generated By:JJTree: Do not edit this line. ASTPommeInt.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeInt_H_
#define ASTPommeInt_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeInt : public PommeNode {
public: 
           ASTPommeInt(int id);
           ASTPommeInt(PommeLexer *parser, int id);
  virtual ~ASTPommeInt();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint64_t m_Value;
};

}

#endif