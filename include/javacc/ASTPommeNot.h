/* Generated By:JJTree: Do not edit this line. ASTPommeNot.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeNot_H_
#define ASTPommeNot_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeNot : public PommeNode {
public: 
           ASTPommeNot(int id);
           ASTPommeNot(PommeLexer *parser, int id);
  virtual ~ASTPommeNot();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  bool convertBool = false;
  uint16_t index;
  bool native;
};

}

#endif
