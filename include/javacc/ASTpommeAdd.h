/* Generated By:JJTree: Do not edit this line. ASTpommeAdd.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeAdd_H_
#define ASTpommeAdd_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeAdd : public PommeNode {
public: 
           ASTpommeAdd(int id);
           ASTpommeAdd(PommeLexer *parser, int id);
  virtual ~ASTpommeAdd();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
