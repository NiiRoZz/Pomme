/* Generated By:JJTree: Do not edit this line. ASTpommeStatic.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeStatic_H_
#define ASTpommeStatic_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeStatic : public PommeNode {
public: 
           ASTpommeStatic(int id);
           ASTpommeStatic(PommeLexer *parser, int id);
  virtual ~ASTpommeStatic();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
