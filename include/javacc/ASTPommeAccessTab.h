/* Generated By:JJTree: Do not edit this line. ASTPommeAccessTab.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTPommeAccessTab_H_
#define ASTPommeAccessTab_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTPommeAccessTab : public PommeNode {
public: 
           ASTPommeAccessTab(int id);
           ASTPommeAccessTab(PommeLexer *parser, int id);
  virtual ~ASTPommeAccessTab();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  uint16_t index;
  bool native;
};

}

#endif