#pragma once

#include "States/State.hpp"
#include <map>

namespace States
{
    class StateMachine
    {
    protected:
        States::stateID runnigStateID;
        States::stateID lastStateID;

        std::map<stateID, State *> mapOfStates;

    public:
        StateMachine();

        virtual ~StateMachine();

        void changeState(States::stateID id);

        void updateState(const float dt);

        void renderState();

        States::stateID getStateID() const;

        void insertState(States::State *pState);

        States::stateID getLastStateID() const;
    };

} // namespace States
