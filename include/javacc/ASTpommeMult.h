/* Generated By:JJTree: Do not edit this line. ASTpommeMult.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeMult_H_
#define ASTpommeMult_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeMult : public PommeNode {
public: 
           ASTpommeMult(int id);
           ASTpommeMult(PommeLexer *parser, int id);
  virtual ~ASTpommeMult();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
