/* Generated By:JJTree: Do not edit this line. ASTvoidType.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTvoidType_H_
#define ASTvoidType_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTvoidType : public PommeNode {
public: 
           ASTvoidType(int id);
           ASTvoidType(PommeLexer *parser, int id);
  virtual ~ASTvoidType();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
