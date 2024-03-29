/* Generated By:JavaCC: Do not edit this line. JJTPommeLexerState.h Version 7.0 */
/* JavaCCOptions: */
#ifndef JAVACC_JJTPommeLexerState_H
#define JAVACC_JJTPommeLexerState_H

#include <set>
#include <vector>
#include "JavaCC.h"
#include "Node.h"

using namespace std;

namespace Pomme {
class JJTPommeLexerState {
private: 
  vector<Node*>* nodes;
  vector<int>*   marks;
  set<Node*>*    open_nodes;

  int            sp;        // number of nodes on stack
  int            mk;        // current mark
  bool           node_created;

public:
            JJTPommeLexerState();
   virtual ~JJTPommeLexerState();

  /* Determines whether the current node was actually closed and
     pushed.  This should only be called in the final user action of a
     node scope.  */
  virtual bool nodeCreated();

  /* Call this to reinitialize the node stack.  It is called
     automatically by the parser's ReInit() method. */
  virtual void reset();

  /* Returns the root node of the AST.  It only makes sense to call
     this after a successful parse. */
  virtual Node *rootNode();

  /* Pushes a node on to the stack. */
  virtual void pushNode(Node *n);

  /* Returns the node on the top of the stack, and remove it from the stack.  */
  virtual Node *popNode();

  /* Returns the node currently on the top of the stack. */
  virtual Node *peekNode();

  /* Returns the number of children on the stack in the current node scope. */
  virtual int nodeArity();


  virtual void clearNodeScope(Node *n);


  virtual void openNodeScope(Node *n);


  /* A definite node is constructed from a specified number of
     children.  That number of nodes are popped from the stack and
     made the children of the definite node.  Then the definite node
     is pushed on to the stack. */
  virtual void closeNodeScope(Node *n, int num);


  /* A conditional node is constructed if its condition is true.  All
     the nodes that have been pushed since the node was opened are
     made children of the conditional node, which is then pushed
     on to the stack.  If the condition is false the node is not
     constructed and they are left on the stack. */
  virtual void closeNodeScope(Node *n, bool condition);
  /* Remove nodes */
  public: void clear();
};

}

#endif
/* JavaCC - OriginalChecksum=d9c91e811d4a23b243ce13bb3b549052 (do not edit this line) */
