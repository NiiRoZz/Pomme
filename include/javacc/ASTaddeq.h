/* Generated By:JJTree: Do not edit this line. ASTaddeq.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTaddeq_H_
#define ASTaddeq_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTaddeq : public PommeNode {
public: 
           ASTaddeq(int id);
           ASTaddeq(PommeLexer *parser, int id);
  virtual ~ASTaddeq();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
};

}

#endif
