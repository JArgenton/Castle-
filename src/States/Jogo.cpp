#include "States/Jogo.hpp"
#include "Menus/MainMenu.hpp"
#include "States/Level.hpp"

namespace States
{

    Jogo::Jogo() : pGraphicManager(Managers::Graphics::get_instance()),
                   pEventManager(Managers::EventsManager::getInstance())
    {
        clock.restart();
        dt = 0;
        State *pStates = nullptr;
        pStates = static_cast<State *>(new Menus::MainMenuState(this));
        insertState(pStates);

        pStates = static_cast<State *>(new Level(this));
        insertState(pStates);

        changeState(stateID::MAINMENU);
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
            pGraphicManager->updateDeltaTime();

            updateState(pGraphicManager->getDeltaTime());

            renderState();

            pGraphicManager->display();
        }
    }

    void Jogo::endJogo()
    {
        pGraphicManager->closeWindow();
    }

}