/* Generated By:JJTree: Do not edit this line. ASTpommeModdedClass.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef ASTpommeModdedClass_H_
#define ASTpommeModdedClass_H_

#include "PommeNode.h"

namespace Pomme {
class PommeLexer;

class ASTpommeModdedClass : public PommeNode {
public: 
           ASTpommeModdedClass(int id);
           ASTpommeModdedClass(PommeLexer *parser, int id);
  virtual ~ASTpommeModdedClass();

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data);

  std::string defaultClassName;
  std::string parentName;
};

}

#endif
