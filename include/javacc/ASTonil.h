/* Generated By:JJTree: Do not edit this line. ASTonil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTonil_H_
#define ASTonil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTonil : public PommeNode {
public: 
           ASTonil(int id);
           ASTonil(PommeLexer *parser, int id);
  virtual ~ASTonil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
