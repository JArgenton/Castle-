#include "States/State.hpp"

#include "States/StateMachine.hpp"
#include <iostream>

namespace States
{

    State::State(StateMachine *pSM, States::stateID id) : pStateMachine(pSM),
                                                          id(id) {}

    State::~State()
    {
        pStateMachine = nullptr;
    }

    void State::setStateMachine(StateMachine *pSM)
    {
        this->pStateMachine = pSM;
    }

    void State::changeState(States::stateID id)
    {
        pStateMachine->changeState(id);
    }

    States::stateID State::getID() const
    {
        return id;
    }

} // namespace States