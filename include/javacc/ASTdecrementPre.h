/* Generated By:JJTree: Do not edit this line. ASTdecrementPre.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTdecrementPre_H_
#define ASTdecrementPre_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTdecrementPre : public PommeNode {
public: 
           ASTdecrementPre(int id);
           ASTdecrementPre(PommeLexer *parser, int id);
  virtual ~ASTdecrementPre();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
