/* Generated By:JJTree: Do not edit this line. ASTheader.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTheader_H_
#define ASTheader_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTheader : public PommeNode {
public: 
           ASTheader(int id);
           ASTheader(PommeLexer *parser, int id);
  virtual ~ASTheader();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
