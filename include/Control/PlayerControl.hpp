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
        Entities::Characters::Player *pPlayer;
        State *id;

    public:
        PlayerControl(Entities::Characters::Player *pP = NULL);

        ~PlayerControl();

        void notifyPressed(std::string key);

        void notifyReleased(std::string key);

        void setPlayer(Entities::Characters::Player *pP);
    };

} // namespace Control