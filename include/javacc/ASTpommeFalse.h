/* Generated By:JJTree: Do not edit this line. ASTpommeFalse.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeFalse_H_
#define ASTpommeFalse_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeFalse : public PommeNode {
public: 
           ASTpommeFalse(int id);
           ASTpommeFalse(PommeLexer *parser, int id);
  virtual ~ASTpommeFalse();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
