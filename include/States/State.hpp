#pragma once

namespace States
{

    class StateMachine;

    enum stateID
    {
        UNKNOWN = -1,
        MAINMENU = 0,
        PLAYING = 1
    };

    class State
    {

    protected:
        StateMachine *pStateMachine;
        stateID id;

    public:
        State(StateMachine *pSM = nullptr, States::stateID id = UNKNOWN);

        virtual ~State();

        void setStateMachine(StateMachine *pSM);

        void changeState(States::stateID id);

        States::stateID getID() const;

        virtual void update(const float dt) = 0;

        virtual void render() = 0;

        virtual void resetState() = 0;
    };

}