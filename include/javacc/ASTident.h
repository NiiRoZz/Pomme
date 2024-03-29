/* Generated By:JJTree: Do not edit this line. ASTident.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTident_H_
#define ASTident_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTident : public PommeNode {
public: 
           ASTident(int id);
           ASTident(PommeLexer *parser, int id);
  virtual ~ASTident();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const ;

  std::string m_Identifier;
};

}

#endif
