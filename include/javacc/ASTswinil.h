/* Generated By:JJTree: Do not edit this line. ASTswinil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTswinil_H_
#define ASTswinil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTswinil : public PommeNode {
public: 
           ASTswinil(int id);
           ASTswinil(PommeLexer *parser, int id);
  virtual ~ASTswinil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
