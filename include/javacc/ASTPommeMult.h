/* Generated By:JJTree: Do not edit this line. ASTPommeMult.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeMult_H_
#define ASTPommeMult_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeMult : public PommeNode {
public: 
           ASTPommeMult(int id);
           ASTPommeMult(PommeLexer *parser, int id);
  virtual ~ASTPommeMult();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif