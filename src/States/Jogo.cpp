#include "States/Jogo.hpp"
#include "Menus/MainMenu.hpp"
#include "Menus/PauseMenu.hpp"
#include "Menus/LeaderBoard.hpp"
#include "Menus/GameOver.hpp"

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

        pStates = static_cast<State *>(new Menus::PauseMenu(this));
        insertState(pStates);

        pStates = static_cast<State *>(new Menus::LeaderBoard(this));
        insertState(pStates);

        pStates = static_cast<State *>(new Level(this));
        insertState(pStates);

        pStates = static_cast<State *>(new Menus::GameOver(this, dynamic_cast<States::Level *>(mapOfStates[stateID::FASE])));
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