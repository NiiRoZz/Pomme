/* Generated By:JJTree: Do not edit this line. ASTPommeModulo.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeModulo_H_
#define ASTPommeModulo_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeModulo : public PommeNode {
public: 
           ASTPommeModulo(int id);
           ASTPommeModulo(PommeLexer *parser, int id);
  virtual ~ASTPommeModulo();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif