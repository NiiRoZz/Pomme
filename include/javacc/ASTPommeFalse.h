/* Generated By:JJTree: Do not edit this line. ASTPommeFalse.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeFalse_H_
#define ASTPommeFalse_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeFalse : public PommeNode {
public: 
           ASTPommeFalse(int id);
           ASTPommeFalse(PommeLexer *parser, int id);
  virtual ~ASTPommeFalse();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif