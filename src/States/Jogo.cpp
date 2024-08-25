#include "States/Jogo.hpp"
#include "Menus/MainMenu.hpp"

namespace States
{

    Jogo::Jogo() : pGraphicManager(Managers::Graphics::get_instance()),
                   pEventManager(Managers::EventsManager::getInstance())
    {
        clock.restart();
        dt = 0;

        State *states = static_cast<State *>(new Menus::MainMenuState(this));
        insertState(states);

        changeState(stateID::MAINMENU);

        exec();
    }

    Jogo::~Jogo()
    {
    }

    void Jogo::exec()
    {
        while (pGraphicManager->isWindowOpen())
        {

            pEventManager->pollEvents();

            pGraphicManager->clear();

            if (dt < TICK_RATE)
            {
                dt += clock.getElapsedTime().asSeconds();
                clock.restart();
            } //
            else
            {
                updateState(0.01);
                dt -= TICK_RATE;
            }

            renderState();

            pGraphicManager->display();
        }
    }

    void Jogo::endJogo()
    {
        pGraphicManager->closeWindow();
    }

}