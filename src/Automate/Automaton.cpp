#include "Automaton.h"

#include <iostream>
#include <algorithm>


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
    
    bool Automaton::addTransition(int from, int to){
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
                    std::cout << "b " << it->second.size() << std::endl;
                    it->second.erase(it->second.begin() + index);
                    std::cout << "a " << it->second.size() << std::endl;
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
}
