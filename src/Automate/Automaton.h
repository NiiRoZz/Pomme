#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <SimpleNode.h>
#include <TypeCheckerVisitor.h>
#include "Transition.h"
#include "State.h"

namespace Pomme {

    class Automaton {

    private :
        std::map<int, State> m_state;
        std::map<int, std::vector<Transition>> m_transition;

    public:
        std::string loop;
        bool addState(int state);
        bool removeState(int state);
        bool hasState(int state) const;
        std::size_t countStates() const;
        void setStateInitial(int state);
        bool isStateInitial(int state) const;
        void setStateFinal(int state);
        bool isStateFinal(int state) const;
        State * getState(int state);
        int getState(const std::string& name);
        std::vector<Transition> getTransitionsExiting(int state);

        bool addTransition(int from, int to);
        bool removeTransition(int from, int to);
        bool hasTransition(int from, int to) const;
        std::size_t countTransitions() const;

        bool hasLoop();
        std::vector<int> topologicalSort();
        bool processDFSTree(int state, std::vector<bool>* visited, std::vector<int>* stack);
        void printCycle(int state, const std::vector<int>* stack);
        bool isStateIndependant(int state);
        std::vector<Node *> getClassNode(const std::vector<int>* class_order);

        friend std::ostream & operator<<(std::ostream & str, const Automaton & klass)
        {
          for(const auto& it : klass.m_state)
          {
              str << it.second << std::endl;
          }
          for(const auto& it : klass.m_transition)
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
