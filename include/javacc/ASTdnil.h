/* Generated By:JJTree: Do not edit this line. ASTdnil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTdnil_H_
#define ASTdnil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTdnil : public PommeNode {
public: 
           ASTdnil(int id);
           ASTdnil(PommeLexer *parser, int id);
  virtual ~ASTdnil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
