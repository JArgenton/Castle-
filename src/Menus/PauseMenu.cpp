#include "Menus/PauseMenu.hpp"
#include "States/Game.hpp"

#define BACKGROUND "assets/BackGrounds/OutSideCastle.png" // arte por ia copilot
// por que ela desconfigurou sozinha? °-°

// inspirado na configuração do monitor Burda

namespace Menus
{
    PauseMenu::PauseMenu(States::Game *pG) : Menu(),
                                             State(static_cast<States::StateMachine *>(pG), States::stateID::PAUSEMENU),
                                             pJogo(pG),
                                             title()
    {
        Managers::Graphics *graphM = Managers::Graphics::get_instance();
        GraphicalElements::Button *bt = NULL;

        bt = new GraphicalElements::Button(TupleF(graphM->getWindowSize().x / 2, graphM->getWindowSize().y / 2), "Return Game");
        bt->select(true);
        vectorOfButtons.push_back(bt);

        bt = new GraphicalElements::Button(TupleF(graphM->getWindowSize().x / 2, (graphM->getWindowSize().y / 2) + 100), "quit to Main Menu");
        vectorOfButtons.push_back(bt);

        bt = new GraphicalElements::Button(TupleF(graphM->getWindowSize().x / 2, (graphM->getWindowSize().y / 2) + 200), "Save and quit");
        vectorOfButtons.push_back(bt);

        title.setTextInfo("Pause");
        title.setFontSize(100);
        title.setTextColor(0.6, 168.2, 144.3);
        title.setTextAlignment(GraphicalElements::TextAlignment::center);
        title.setPosition(TupleF(graphM->getWindowSize().x / 2.0f, 150.0f - title.getSize().y / 2));

        back.initialize(BACKGROUND, TupleF(graphM->getWindowSize().x / 2.0f, graphM->getWindowSize().y / 2), TupleF(graphM->getWindowSize().x, graphM->getWindowSize().y));

        max = 2;
    }

    PauseMenu::~PauseMenu()
    {
    }

    void PauseMenu::execute()
    {
        if (active)
        {
            active = false;
            switch (selected)
            {
            case 0:
                changeState(pStateMachine->getLastStateID());
                break;

            case 1:
                changeState(States::stateID::MAINMENU);
                break;

            case 2:
            {
                States::Level *currentLevel = dynamic_cast<States::Level *>(pJogo->getState(pStateMachine->getLastStateID()));
                if (currentLevel)
                {
                    currentLevel->saveGameState("Saves/SAVEGAME.json"); // Salvar o jogo
                }
                pJogo->endGame();
                break;
            }

            default:
                break;
            }
        }
    }

    void PauseMenu::resetState()
    {
        for (it = vectorOfButtons.begin(); it != vectorOfButtons.end(); ++it)
            (*it)->select(false);
        selected = 0;
        vectorOfButtons[selected]->select(true);
        active = true;
    }

    void PauseMenu::render()
    {
        updateView();
        back.render();
        for (it = vectorOfButtons.begin(); it != vectorOfButtons.end(); ++it)
            (*it)->render();

        title.render();
    }

    void PauseMenu::update(float dt)
    {
    }

    void PauseMenu::initPause()
    {
        if (pStateMachine->getStateID() == States::stateID::LEVEL1 || pStateMachine->getStateID() == States::stateID::LEVEL2)
        {
            changeState(States::stateID::PAUSEMENU);
        }
    }

    States::Level *PauseMenu::getCurrentLevel()
    {

        return dynamic_cast<States::Level *>(pJogo->getState(pStateMachine->getLastStateID()));
    }
} // namespace Menus
