/* Generated By:JJTree: Do not edit this line. ASTaccessTab.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTaccessTab_H_
#define ASTaccessTab_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTaccessTab : public PommeNode {
public: 
           ASTaccessTab(int id);
           ASTaccessTab(PommeLexer *parser, int id);
  virtual ~ASTaccessTab();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);
};

}

#endif
