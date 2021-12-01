/* Generated By:JJTree: Do not edit this line. ASTpommeMinus.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeMinus_H_
#define ASTpommeMinus_H_

#include "PommeNode.h"
#include "VM/Chunk.h"

namespace Pomme {
class PommeLexer;

class ASTpommeMinus : public PommeNode {
public: 
           ASTpommeMinus(int id);
           ASTpommeMinus(PommeLexer *parser, int id);
  virtual ~ASTpommeMinus();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
  bool primitive = false;
  OpCode opCode;
};

}

#endif
