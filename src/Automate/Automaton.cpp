#include "Automaton.h"

#include <iostream>
#include <algorithm>
#include <queue>


namespace Pomme {
    
    std::size_t Automaton::countStates() const
    {
        if(this->m_state.empty())
        {
            return 0;
        }
        return this->m_state.size();
    }

    std::size_t Automaton::countTransitions() const
    {
        int result = 0;
        for(const auto& it : this->m_transition)
        {
            result += it.second.size();
        }
        return result;
    }
    
    bool Automaton::addState(int state)
    {
        if(state >= 0){
            auto it = this->m_state.find(state);
            if(it != this->m_state.end())
            {
                return false;
            }else
            {
                State node(state);
                this->m_state.insert(std::pair<int,State>(state, node));
                return true;
            }
        }
        return false;
    }
    
    bool Automaton::removeState(int state)
    {
        auto it = this->m_state.find(state);
        if(it != this->m_state.end())
        {
            this->m_state.erase(state);
            return true;
        }

        return false;
    }
    
    bool Automaton::hasState(int state) const
    {
        auto it = this->m_state.find(state);
        if( it != this->m_state.end() )
        {
            return true;
        }
        return false;
    }
    
    bool Automaton::isStateInitial(int state) const
    {
        auto it = this->m_state.find(state);
        if( it != this->m_state.end() )
        {
            return it->second.initialState;
        }
        return false;
    }
    
    bool Automaton::isStateFinal(int state) const
    {
        auto it = this->m_state.find(state);
        if( it != this->m_state.end() )
        {
            return it->second.finalState;
        }
        return false;
    }
    
    bool Automaton::addTransition(int from, int to)
    {
        auto fromState = this->m_state.find(from);
        auto toState = this->m_state.find(to);

        if(fromState == this->m_state.end() || toState == this->m_state.end())
        {
            return false;
        }

        auto it = this->m_transition.find(from);
        if(it != this->m_transition.end())
        {
            for(auto ot : it->second)
            {
                if(ot.from == from && ot.to == to)
                {
                    return false;
                }
            }
            it->second.emplace_back(from,to);
        }else
        {
            std::vector<Transition> vectorTransition;
            vectorTransition.emplace_back(from, to);
            this->m_transition.insert(std::pair<int, std::vector<Transition>>(from, vectorTransition));
        }

        return true;
    }
    
    bool Automaton::removeTransition(int from, int to){
        auto it = this->m_transition.find(from);
        if(it != this->m_transition.end())
        {
            for(unsigned int index = 0; index < it->second.size(); index++)
            {
                if(it->second.at(index).from == from && it->second.at(index).to == to)
                {
                    it->second.erase(it->second.begin() + index);
                }
            }
            return true;
        }
        return false;
    }
    
    bool Automaton::hasTransition(int from, int to) const{
        auto it = this->m_transition.find(from);
        if(it != this->m_transition.end())
        {
            for(auto ot : it->second)
            {
                if(ot.from == from && ot.to == to)
                {
                    return true;
                }
            }
        }
        return false;
    }
    
    void Automaton::setStateInitial(int state)
    {
        auto it = this->m_state.find(state);
        if( it != this->m_state.end() )
        {
            it->second.initialState = true;
        }
    }

    void Automaton::setStateFinal(int state)
    {
        auto it = this->m_state.find(state);
        if( it != this->m_state.end() )
        {
            it->second.finalState = true;
        }
    }

    State* Automaton::getState(int state)
    {
        auto it = this->m_state.find(state);
        if(it != this->m_state.end())
        {
            return &it->second;
        }
        return nullptr;
    }

    int Automaton::getState(const std::string& name)
    {
        for(auto it : this->m_state)
        {
            std::cout << dynamic_cast<ASTident*>(it.second.node->jjtGetChild(0))->m_Identifier << std::endl;

            if( dynamic_cast<ASTident*>(it.second.node->jjtGetChild(0))->m_Identifier == name)
            {
                return it.second.name;
            }
        }
        return -1;
    }

    std::vector<int> Automaton::topologicalSort()
    {
        const int nbState = this->countStates() - 1;
        std::vector<int> independant_state;
        std::vector<int> order;
        std::vector<Transition> toDelete;

        for(int state = 0; state <= nbState ; state++)
        {
            independant_state.push_back(state);
        }
        for(int state = 0; state <= nbState ; state++)
        {
           auto it = this->m_transition.find(state);
           if(it != this->m_transition.end())
           {
               for(auto ot : it->second)
               {
                   independant_state.erase(std::remove(independant_state.begin(), independant_state.end(), ot.to), independant_state.end());
               }
           }
        }

        while(!independant_state.empty())
        {
            int state = independant_state.at(0);
            independant_state.erase(std::remove(independant_state.begin(), independant_state.end(), independant_state.at(0)), independant_state.end());
            if(std::find(order.begin(), order.end(), state) == order.end())
            {
                order.push_back(state);
            }
            auto it = this->m_transition.find(state);
            if(it != this->m_transition.end())
            {
                for(auto ut : it->second)
                {
                    toDelete.push_back(ut);
                }
            }

            for(auto ot : toDelete)
            {
                this->removeTransition(ot.from, ot.to);
                if(isStateIndependant(ot.to))
                {
                    independant_state.push_back(ot.to);
                }
            }
            toDelete.clear();
        }

        return order;
    }

    bool Automaton::isStateIndependant(int state)
    {
        int nbState = this->countStates() - 1;
        for(int stateIndex = 0; stateIndex <= nbState; stateIndex++)
        {
            if(this->hasTransition(stateIndex,state))
            {
                return false;
            }
        }
        return true;
    }

    bool Automaton::hasLoop()
    {
        std::vector<bool> visited;
        int maxState = this->countStates() - 1;
        for(int i = 0 ; i <= maxState; i++)
        {
            visited.push_back(false);
        }

        std::vector<int> stack;
        for(int state = 0; state <= maxState; state++)
        {
            stack.clear();
            stack.push_back(state);
            visited.at(state) = true;
            if(processDFSTree(state, &visited, &stack))
            {
                return true;
            }
        }
        return false;
    }

    bool Automaton::processDFSTree(int state, std::vector<bool>* visited, std::vector<int>* stack)
    {
        auto it = this->m_transition.find(state);
        if(it != this->m_transition.end())
        {
            for(auto ot : it->second)
            {
                if(std::find(stack->begin(), stack->end(), ot.to) != stack->end())
                {
                    printCycle(state, stack);
                    return true;
                }else
                {
                    stack->push_back(ot.to);
                    visited->at(ot.to) = true;
                    return processDFSTree(ot.to, visited, stack);
                }
            }
        }
        return false;
    }

    void Automaton::printCycle(int state, const std::vector<int>* stack)
    {
        std::cout << "PRINTING CYCLE" <<std::endl;
        for(auto i : *stack)
        {
            std::cout << i << std::endl;
            if(i == state)
            {
                std::cout << std::endl;
                break;
            }
        }
    }
}
