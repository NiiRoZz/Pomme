/* Generated By:JJTree: Do not edit this line. ASTPommeDecrPre.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeDecrPre_H_
#define ASTPommeDecrPre_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeDecrPre : public PommeNode {
public: 
           ASTPommeDecrPre(int id);
           ASTPommeDecrPre(PommeLexer *parser, int id);
  virtual ~ASTPommeDecrPre();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif