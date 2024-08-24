#include "States/StateMachine.hpp"

#include "States/State.hpp"

#include <iostream>

namespace States
{

    StateMachine::StateMachine()
    {
        lastStateID = stateID::UNKNOWN;
        runnigStateID = stateID::UNKNOWN;
    }

    StateMachine::~StateMachine()
    {
        std::map<stateID, State *>::iterator it;

        for (it = mapOfStates.begin(); it != mapOfStates.end(); ++it)
        {
            delete (it->second);
        }
    }

    void StateMachine::changeState(States::stateID id)
    {
        lastStateID = runnigStateID;
        runnigStateID = id;
        mapOfStates[runnigStateID]->resetState();
    }

    void StateMachine::updateState(const float dt)
    {
        mapOfStates[runnigStateID]->update(dt);
    }

    void StateMachine::renderState()
    {
        mapOfStates[runnigStateID]->render();
    }

    stateID StateMachine::getStateID() const
    {
        return runnigStateID;
    }

    void StateMachine::insertState(States::State *pState)
    {
        if (pState == nullptr)
        {
            std::cout << "ERRO ponteiro nulo StateMachine::insertState()" << std::endl;
            exit(1);
        }
        mapOfStates.insert(std::pair<stateID, State *>(pState->getID(), pState));
    }

    States::stateID StateMachine::getLastStateID() const
    {
        return lastStateID;
    }

} // namespace States