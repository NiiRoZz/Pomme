/* Generated By:JJTree: Do not edit this line. ASTdecrementPost.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTdecrementPost_H_
#define ASTdecrementPost_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTdecrementPost : public PommeNode {
public: 
           ASTdecrementPost(int id);
           ASTdecrementPost(PommeLexer *parser, int id);
  virtual ~ASTdecrementPost();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif