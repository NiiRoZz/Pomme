/* Generated By:JJTree: Do not edit this line. ASTidentOp.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTidentOp_H_
#define ASTidentOp_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTidentOp : public PommeNode {
public: 
           ASTidentOp(int id);
           ASTidentOp(PommeLexer *parser, int id);
  virtual ~ASTidentOp();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
