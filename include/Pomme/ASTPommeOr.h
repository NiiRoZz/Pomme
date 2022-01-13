/* Generated By:JJTree: Do not edit this line. ASTPommeOr.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeOr_H_
#define ASTPommeOr_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeOr : public PommeNode {
public: 
           ASTPommeOr(int id);
           ASTPommeOr(PommeLexer *parser, int id);
  virtual ~ASTPommeOr();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  bool convertLeftBool = false;
  uint16_t leftIndex;
  bool leftNative;

  bool convertRightBool = false;
  uint16_t rightIndex;
  bool rightNative;
};

}

#endif