/* Generated By:JJTree: Do not edit this line. ASTpommeConstant.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeConstant_H_
#define ASTpommeConstant_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeConstant : public PommeNode {
public: 
           ASTpommeConstant(int id);
           ASTpommeConstant(PommeLexer *parser, int id);
  virtual ~ASTpommeConstant();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
