/* Generated By:JJTree: Do not edit this line. ASTidentFuncs.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTidentFuncs_H_
#define ASTidentFuncs_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTidentFuncs : public PommeNode {
public: 
           ASTidentFuncs(int id);
           ASTidentFuncs(PommeLexer *parser, int id);
  virtual ~ASTidentFuncs();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
