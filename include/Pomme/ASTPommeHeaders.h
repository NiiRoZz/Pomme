/* Generated By:JJTree: Do not edit this line. ASTPommeHeaders.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeHeaders_H_
#define ASTPommeHeaders_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeHeaders : public PommeNode {
public: 
           ASTPommeHeaders(int id);
           ASTPommeHeaders(PommeLexer *parser, int id);
  virtual ~ASTPommeHeaders();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif