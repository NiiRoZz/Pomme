/* Generated By:JJTree: Do not edit this line. ASTscinil.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTscinil_H_
#define ASTscinil_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTscinil : public PommeNode {
public: 
           ASTscinil(int id);
           ASTscinil(PommeLexer *parser, int id);
  virtual ~ASTscinil();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
