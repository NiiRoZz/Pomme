/* Generated By:JJTree: Do not edit this line. ASTpommeArray.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeArray_H_
#define ASTpommeArray_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeArray : public PommeNode {
public: 
           ASTpommeArray(int id);
           ASTpommeArray(PommeLexer *parser, int id);
  virtual ~ASTpommeArray();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;
};

}

#endif
