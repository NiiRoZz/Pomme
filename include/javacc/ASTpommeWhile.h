/* Generated By:JJTree: Do not edit this line. ASTpommeWhile.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeWhile_H_
#define ASTpommeWhile_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeWhile : public PommeNode {
public: 
           ASTpommeWhile(int id);
           ASTpommeWhile(PommeLexer *parser, int id);
  virtual ~ASTpommeWhile();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
