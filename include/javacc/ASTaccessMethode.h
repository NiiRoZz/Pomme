/* Generated By:JJTree: Do not edit this line. ASTaccessMethode.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTaccessMethode_H_
#define ASTaccessMethode_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTaccessMethode : public PommeNode {
public: 
           ASTaccessMethode(int id);
           ASTaccessMethode(PommeLexer *parser, int id);
  virtual ~ASTaccessMethode();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
