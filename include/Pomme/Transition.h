#ifndef TRANSITION_H
#define TRANSITION_H

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include "State.h"


namespace Pomme {
       

  class Transition {
    public:
        int from;
        int to;

        Transition(int from, int to):
        from(from),
        to(to)
        {
        }

      friend std::ostream & operator<<(std::ostream & str, const Transition & klass)
      {
          str << klass.from << " -> " << klass.to;
          return str;
      }
  };
  
}

#endif // TRANSITION_H
