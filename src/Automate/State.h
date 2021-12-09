#ifndef STATE_H
#define STATE_H

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <SimpleNode.h>


namespace Pomme {
       

  class State {
    public:
        int name;
        bool finalState;
        bool initialState;
        Node* node;

        bool modded;
        bool extend;
        bool global;

        State(int name):
        name(name),
        finalState(false),
        initialState(false),
        node(nullptr),
        modded(false),
        extend(false),
        global(false)
        {

        }

      friend std::ostream & operator<<(std::ostream & str, const State & klass)
      {
          str << klass.name << "[final:" << klass.initialState << ", initial:" << klass.finalState << "]";
          return str;
      }
  };
  
}

#endif // STATE_H
