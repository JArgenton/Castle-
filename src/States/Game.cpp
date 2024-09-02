#include "States/Game.hpp"
#include "Menus/MainMenu.hpp"
#include "Menus/PauseMenu.hpp"
#include "Menus/LeaderBoard.hpp"
#include "Menus/GameOver.hpp"

#include "States/LevelOutterCastle.hpp"
#include "States/LevelInnerClastle.hpp"

namespace States
{

    Game::Game() : pGraphicManager(Managers::Graphics::get_instance()),
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

        pStates = static_cast<State *>(new OutterCastle(this));
        insertState(pStates);

        pStates = static_cast<State *>(new InnerCastle(this));
        insertState(pStates);

        pStates = static_cast<State *>(new Menus::GameOver(this, dynamic_cast<States::Level *>(mapOfStates[stateID::LEVEL1])));
        insertState(pStates);

        changeState(stateID::MAINMENU);
    }

    Game::~Game()
    {
    }

    void Game::exec()
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

    void Game::endGame()
    {
        pGraphicManager->closeWindow();
    }

    State *Game::getState(stateID id)
    {
        auto it = mapOfStates.find(id);
        if (it != mapOfStates.end())
        {
            return it->second;
        }
        return nullptr;
    }

}