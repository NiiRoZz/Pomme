/* Generated By:JJTree: Do not edit this line. ASTpommePrint.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommePrint_H_
#define ASTpommePrint_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommePrint : public PommeNode {
public: 
           ASTpommePrint(int id);
           ASTpommePrint(PommeLexer *parser, int id);
  virtual ~ASTpommePrint();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
