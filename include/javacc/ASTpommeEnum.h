/* Generated By:JJTree: Do not edit this line. ASTpommeEnum.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeEnum_H_
#define ASTpommeEnum_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeEnum : public PommeNode {
public: 
           ASTpommeEnum(int id);
           ASTpommeEnum(PommeLexer *parser, int id);
  virtual ~ASTpommeEnum();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
