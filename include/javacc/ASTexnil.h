/* Generated By:JJTree: Do not edit this line. ASTexnil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTexnil_H_
#define ASTexnil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTexnil : public PommeNode {
public: 
           ASTexnil(int id);
           ASTexnil(PommeLexer *parser, int id);
  virtual ~ASTexnil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
