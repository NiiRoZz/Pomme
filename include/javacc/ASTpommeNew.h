/* Generated By:JJTree: Do not edit this line. ASTpommeNew.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeNew_H_
#define ASTpommeNew_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeNew : public PommeNode {
public: 
           ASTpommeNew(int id);
           ASTpommeNew(PommeLexer *parser, int id);
  virtual ~ASTpommeNew();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif