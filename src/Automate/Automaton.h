#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Transition.h"
#include "State.h"

namespace Pomme {

    class Automaton {

        
    private :
        std::map<int, State> m_state;
        std::map<int, std::vector<Transition>> m_transition;
    
    public:
        
    //state
    bool addState(int state);
    bool removeState(int state);
    bool hasState(int state) const ;
    std::size_t countStates() const;
    void setStateInitial(int state) ;
    bool isStateInitial(int state) const ;
    void setStateFinal(int state) ;
    bool isStateFinal(int state) const ;

    bool addTransition(int from, int to);
    bool removeTransition(int from, int to );
    bool hasTransition(int from, int to) const;
    std::size_t countTransitions() const;

      friend std::ostream & operator<<(std::ostream & str, const Automaton & klass)
      {
          for(auto it : klass.m_state)
          {
              str << it.second << std::endl;
          }
          for(auto it : klass.m_transition)
          {
              for(auto ot : it.second)
              {
                  str << ot << std::endl;
              }
          }
          return str;
      }
    };

}

#endif // AUTOMATON_H
