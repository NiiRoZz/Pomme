/* Generated By:JJTree: Do not edit this line. ASTpommeFloat.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeFloat_H_
#define ASTpommeFloat_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeFloat : public PommeNode {
public: 
           ASTpommeFloat(int id);
           ASTpommeFloat(PommeLexer *parser, int id);
  virtual ~ASTpommeFloat();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  float m_Value;
};

}

#endif
