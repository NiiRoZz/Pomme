/* Generated By:JJTree: Do not edit this line. ASTpommeTrue.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeTrue_H_
#define ASTpommeTrue_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeTrue : public PommeNode {
public: 
           ASTpommeTrue(int id);
           ASTpommeTrue(PommeLexer *parser, int id);
  virtual ~ASTpommeTrue();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif