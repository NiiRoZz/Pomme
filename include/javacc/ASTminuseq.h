/* Generated By:JJTree: Do not edit this line. ASTminuseq.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTminuseq_H_
#define ASTminuseq_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTminuseq : public PommeNode {
public: 
           ASTminuseq(int id);
           ASTminuseq(PommeLexer *parser, int id);
  virtual ~ASTminuseq();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
};

}

#endif
