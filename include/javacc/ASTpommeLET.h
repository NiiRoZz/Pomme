/* Generated By:JJTree: Do not edit this line. ASTpommeLET.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeLET_H_
#define ASTpommeLET_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeLET : public PommeNode {
public: 
           ASTpommeLET(int id);
           ASTpommeLET(PommeLexer *parser, int id);
  virtual ~ASTpommeLET();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
