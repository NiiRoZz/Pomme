/* Generated By:JJTree: Do not edit this line. ASTPommeOnil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeOnil_H_
#define ASTPommeOnil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeOnil : public PommeNode {
public: 
           ASTPommeOnil(int id);
           ASTPommeOnil(PommeLexer *parser, int id);
  virtual ~ASTPommeOnil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif