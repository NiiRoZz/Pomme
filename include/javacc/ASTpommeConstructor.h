/* Generated By:JJTree: Do not edit this line. ASTpommeConstructor.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeConstructor_H_
#define ASTpommeConstructor_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeConstructor : public PommeNode {
public: 
           ASTpommeConstructor(int id);
           ASTpommeConstructor(PommeLexer *parser, int id);
  virtual ~ASTpommeConstructor();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
};

}

#endif
