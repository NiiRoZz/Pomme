/* Generated By:JJTree: Do not edit this line. ASTPommeInil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeInil_H_
#define ASTPommeInil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeInil : public PommeNode {
public: 
           ASTPommeInil(int id);
           ASTPommeInil(PommeLexer *parser, int id);
  virtual ~ASTPommeInil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
