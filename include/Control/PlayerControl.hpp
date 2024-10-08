#pragma once

#include "Control/Observer.hpp"
#include "Entities/Characters/Player.hpp"
#include "States/StateMachine.hpp"
using namespace States;

namespace Control
{

    class PlayerControl : public Observer
    {
    private:
        StateMachine *pStateM;
        Entities::Characters::Player *pPlayer1;
        Entities::Characters::Player *pPlayer2;

    public:
        PlayerControl(Entities::Characters::Player *pP = NULL);

        ~PlayerControl();

        void notifyPressed(std::string key);

        void notifyReleased(std::string key);

        void setPlayer(Entities::Characters::Player *pP);
        void setMachine(StateMachine *pSTM);
        void reset();
    };

} // namespace Control