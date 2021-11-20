#ifndef STATE_H
#define STATE_H

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>


namespace Pomme {
       

  class State {
    public:
        int name;
        bool finalState;
        bool initialState;

        State(int name):
        name(name),
        finalState(false),
        initialState(false)
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
