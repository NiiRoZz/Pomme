/* Generated By:JJTree: Do not edit this line. ASTpommeEQ.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeEQ_H_
#define ASTpommeEQ_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeEQ : public PommeNode {
public: 
           ASTpommeEQ(int id);
           ASTpommeEQ(PommeLexer *parser, int id);
  virtual ~ASTpommeEQ();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
/* JavaCC - OriginalChecksum=ec5240f2dc7b1835c3d1f1375a97ac62 (do not edit this line) */
