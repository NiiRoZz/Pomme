/* Generated By:JJTree: Do not edit this line. ASTpommeProtected.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeProtected_H_
#define ASTpommeProtected_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeProtected : public PommeNode {
public: 
           ASTpommeProtected(int id);
           ASTpommeProtected(PommeLexer *parser, int id);
  virtual ~ASTpommeProtected();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
