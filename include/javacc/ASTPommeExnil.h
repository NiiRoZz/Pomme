/* Generated By:JJTree: Do not edit this line. ASTPommeExnil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeExnil_H_
#define ASTPommeExnil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeExnil : public PommeNode {
public: 
           ASTPommeExnil(int id);
           ASTPommeExnil(PommeLexer *parser, int id);
  virtual ~ASTPommeExnil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
