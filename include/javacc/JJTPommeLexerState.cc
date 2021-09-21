/* Generated By:JavaCC: Do not edit this line. JJTPommeLexerState.cc Version 7.0 */
/* JavaCCOptions: */
#include "JJTPommeLexerState.h"
#include "Node.h"

namespace Pomme {

#define FIXUP_MARKS \
  if (marks->size() > 0) {\
    mk = marks->back();\
    marks->resize(marks->size()-1);\
  }

  JJTPommeLexerState::JJTPommeLexerState() {
    nodes = new std::vector<Node*>();
    marks = new std::vector<int>();
    open_nodes = new std::set<Node*>();
    sp = 0;
    mk = 0;
  }

  /* Determines whether the current node was actually closed and
     pushed.  This should only be called in the final user action of a
     node scope.  */
  bool JJTPommeLexerState::nodeCreated() {
    return node_created;
  }

  /* Call this to reinitialize the node stack.  It is called
     automatically by the parser's ReInit() method. */
  void JJTPommeLexerState::reset() {
    clear();
    nodes->resize(0);
    marks->resize(0);
    sp = 0;
    mk = 0;
  }

  /* Returns the root node of the AST.  It only makes sense to call
     this after a successful parse. */
  Node *JJTPommeLexerState::rootNode() {
    return nodes->at(0);
  }

  /* Pushes a node on to the stack. */
  void JJTPommeLexerState::pushNode(Node *n) {
    nodes->push_back(n);
    ++sp;
  }

  /* Returns the node on the top of the stack, and remove it from the
     stack.  */
  Node *JJTPommeLexerState::popNode() {
    if (--sp < mk) {
      FIXUP_MARKS;
    }
    Node *ret = nodes->back();
    nodes->resize(nodes->size()-1);
    return ret;
  }

  /* Returns the node currently on the top of the stack. */
  Node *JJTPommeLexerState::peekNode() {
    return nodes->size() == 0 ? nullptr : nodes->back();
  }

  /* Returns the number of children on the stack in the current node
     scope. */
  int JJTPommeLexerState::nodeArity() {
    return sp - mk;
  }


  void JJTPommeLexerState::clearNodeScope(Node *n) {
    while (sp > mk) {
      delete popNode();
    }
    FIXUP_MARKS;
  }


  void JJTPommeLexerState::openNodeScope(Node *n) {
    marks->push_back(mk);
    mk = sp;
    n->jjtOpen();
    open_nodes->insert(n);
  }


  /* A definite node is constructed from a specified number of
     children.  That number of nodes are popped from the stack and
     made the children of the definite node.  Then the definite node
     is pushed on to the stack. */
   void JJTPommeLexerState::closeNodeScope(Node *n, int num) {
    open_nodes->erase(n);
    FIXUP_MARKS;
    if (nodes->size() < num) {
      node_created = false;
      delete n;
      return;
    }
    while (num-- > 0) {
      Node *c = popNode();
      c->jjtSetParent(n);
      n->jjtAddChild(c, num);
    }
    n->jjtClose();
    pushNode(n);
    node_created = true;
  }


  /* A conditional node is constructed if its condition is true.  All
     the nodes that have been pushed since the node was opened are
     made children of the conditional node, which is then pushed
     on to the stack.  If the condition is false the node is not
     constructed and they are left on the stack. */
  void JJTPommeLexerState::closeNodeScope(Node *n, bool condition) {
    open_nodes->erase(n);
    if (condition) {
      unsigned int a = nodeArity();
      FIXUP_MARKS;
      if (nodes->size() < a) {
        delete n;
        node_created = false;
        return;
      }
      while (a-- > 0) {
        Node *c = popNode();
        c->jjtSetParent(n);
        n->jjtAddChild(c, a);
      }
      n->jjtClose();
      pushNode(n);
      node_created = true;
    } else {
      FIXUP_MARKS;
      node_created = false;
      delete n;
    }
  }

  JJTPommeLexerState::~JJTPommeLexerState() {
    clear();
    delete open_nodes;
    delete nodes;
    delete marks;
  }

  void JJTPommeLexerState::clear() {
    for (size_t i = 0; i < nodes->size(); i++) {
      Node* node = nodes->at(i);
      open_nodes->erase(node);
      delete node;
    }
    for (std::set<Node*>::iterator it = open_nodes->begin();
         it != open_nodes->end(); it++) 
      delete (*it);  
  }

}
/* JavaCC - OriginalChecksum=582b5edf81bb4973c0fcae8ecafc22cd (do not edit this line) */
