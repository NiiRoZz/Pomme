/* Generated By:JJTree: Do not edit this line. ASTmulteq.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTmulteq_H_
#define ASTmulteq_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTmulteq : public PommeNode {
public: 
           ASTmulteq(int id);
           ASTmulteq(PommeLexer *parser, int id);
  virtual ~ASTmulteq();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif
