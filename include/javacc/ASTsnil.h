/* Generated By:JJTree: Do not edit this line. ASTsnil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTsnil_H_
#define ASTsnil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTsnil : public PommeNode {
public: 
           ASTsnil(int id);
           ASTsnil(PommeLexer *parser, int id);
  virtual ~ASTsnil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
