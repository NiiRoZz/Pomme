/* Generated By:JJTree: Do not edit this line. ASTdecls.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTdecls_H_
#define ASTdecls_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTdecls : public PommeNode {
public: 
           ASTdecls(int id);
           ASTdecls(PommeLexer *parser, int id);
  virtual ~ASTdecls();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
