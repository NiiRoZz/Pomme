/* Generated By:JJTree: Do not edit this line. ASTpommeMethode.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeMethode_H_
#define ASTpommeMethode_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeMethode : public PommeNode {
public: 
           ASTpommeMethode(int id);
           ASTpommeMethode(PommeLexer *parser, int id);
  virtual ~ASTpommeMethode();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool constructor;
};

}

#endif
