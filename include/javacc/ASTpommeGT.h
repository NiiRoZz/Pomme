/* Generated By:JJTree: Do not edit this line. ASTpommeGT.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeGT_H_
#define ASTpommeGT_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeGT : public PommeNode {
public: 
           ASTpommeGT(int id);
           ASTpommeGT(PommeLexer *parser, int id);
  virtual ~ASTpommeGT();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
