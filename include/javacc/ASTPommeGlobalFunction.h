/* Generated By:JJTree: Do not edit this line. ASTPommeGlobalFunction.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeGlobalFunction_H_
#define ASTPommeGlobalFunction_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeGlobalFunction : public PommeNode {
public: 
           ASTPommeGlobalFunction(int id);
           ASTPommeGlobalFunction(PommeLexer *parser, int id);
  virtual ~ASTPommeGlobalFunction();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif