/* Generated By:JJTree: Do not edit this line. ASTvinil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTvinil_H_
#define ASTvinil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTvinil : public PommeNode {
public: 
           ASTvinil(int id);
           ASTvinil(PommeLexer *parser, int id);
  virtual ~ASTvinil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif