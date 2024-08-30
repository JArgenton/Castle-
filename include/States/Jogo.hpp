#pragma once

#include "Entities/Characters/Player.hpp"
#include "Managers/EventsManager.hpp"
#include "Managers/GraphicManager.hpp"
#include "States/StateMachine.hpp"

#define TICK_RATE 0.0078125

namespace States
{

    class Jogo : public StateMachine
    {
    private:
        Managers::Graphics *pGraphicManager;
        Managers::EventsManager *pEventManager;

        sf::Clock clock;
        float dt;

    public:
        Jogo();

        ~Jogo();

        void exec();

        void endJogo();

        State *getState(stateID id);
    };

} // namespace States