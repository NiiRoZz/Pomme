/* Generated By:JJTree: Do not edit this line. ASTPommeListAccess.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeListAccess_H_
#define ASTPommeListAccess_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeListAccess : public PommeNode {
public: 
           ASTPommeListAccess(int id);
           ASTPommeListAccess(PommeLexer *parser, int id);
  virtual ~ASTPommeListAccess();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
