/* Generated By:JJTree: Do not edit this line. ASTPommePublic.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommePublic_H_
#define ASTPommePublic_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommePublic : public PommeNode {
public: 
           ASTPommePublic(int id);
           ASTPommePublic(PommeLexer *parser, int id);
  virtual ~ASTPommePublic();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
