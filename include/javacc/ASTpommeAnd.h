/* Generated By:JJTree: Do not edit this line. ASTpommeAnd.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeAnd_H_
#define ASTpommeAnd_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeAnd : public PommeNode {
public: 
           ASTpommeAnd(int id);
           ASTpommeAnd(PommeLexer *parser, int id);
  virtual ~ASTpommeAnd();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
