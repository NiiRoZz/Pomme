/* Generated By:JJTree: Do not edit this line. Node.h Version 7.0 */
/* JavaCCOptions:MULTI=true,NODE_USES_PARSER=false,VISITOR=true,TRACK_TOKENS=false,NODE_PREFIX=AST,NODE_EXTENDS=,NODE_FACTORY=,SUPPORT_CLASS_VISIBILITY_PUBLIC=true */
#ifndef JAVACC_NODE_H
#define JAVACC_NODE_H

#include <vector>
#include "JavaCC.h"
#include "Token.h"


namespace Pomme {

/* All AST nodes must implement this interface.  It provides basic
   machinery for constructing the parent and child relationships
   between nodes. */

class PommeLexer;
class PommeLexerVisitor;
class Node {
  friend class SimpleNode;
  
public:
  /** This method is called after the node has been made the current
    node.  It indicates that child nodes can now be added to it. */
  virtual void    jjtOpen() const = 0;

  /** This method is called after all the child nodes have been added. */
  virtual void    jjtClose() const = 0;

  /** This pair of methods are used to inform the node of its parent. */
  virtual void    jjtSetParent(Node *n) = 0;
  virtual Node*   jjtGetParent() const = 0;

  /** This method tells the node to add its argument to the node's list of children.  */
  virtual void    jjtAddChild(Node *n, int i) = 0;

  /** This method returns a child node.  The children are numbered
     from zero, left to right. */
  virtual Node*   jjtGetChild(int i) const = 0;

  /** Return the number of children the node has. */
  virtual int     jjtGetNumChildren() const = 0;
  virtual int     getId() const = 0;

  /** Accept the visitor. **/
  virtual void  jjtAccept(PommeLexerVisitor *visitor, void * data) const = 0;

  /** Clear list of children, and return children that we have before.
      Used in destructor to do linear destruction of tree.
      Since some parsers has subclassed Node, we can't use pure virtual
      function, that would break backward compatibility. */
private: 
  virtual std::vector<Node *> jjtExtractChildrenForDestruction() {
    std::vector<Node *> x;
    return x;
  }
  friend class SimpleNode;

public:
           Node() { }
  virtual ~Node() { }
};


}

#endif
/* JavaCC - OriginalChecksum=a12b1a126733ffd72e632b2dddd41778 (do not edit this line) */
