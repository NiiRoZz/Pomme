/* Generated By:JJTree: Do not edit this line. ASTPommeClass.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeClass_H_
#define ASTPommeClass_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeClass : public PommeNode {
public: 
           ASTPommeClass(int id);
           ASTPommeClass(PommeLexer *parser, int id);
  virtual ~ASTPommeClass();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint64_t nmbMethods = 0;
  uint64_t nmbNativeMethods = 0;
  uint64_t nmbStaticFields = 0;
  uint64_t nmbFields = 0;
};

}

#endif
