/* Generated By:JJTree: Do not edit this line. ASTPommeGT.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeGT_H_
#define ASTPommeGT_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeGT : public PommeNode {
public: 
           ASTPommeGT(int id);
           ASTPommeGT(PommeLexer *parser, int id);
  virtual ~ASTPommeGT();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif