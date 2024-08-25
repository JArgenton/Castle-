#include "Menus/MainMenu.hpp"
#include "Principal.hpp"

namespace Menus
{

    MainMenuState::MainMenuState(Factories::Principal *pP = nullptr) : Menu(),

                                                                       State(static_cast<States::StateMachine *>(pPrin), States::stateID::MAINMENU),
                                                                       pPrin(pP),
                                                                       title()
    {
        Managers::Graphics *GM = Managers::Graphics::get_instance();
        GraphicalElements::Button *bt = NULL;

        bt = new GraphicalElements::Button(TupleF(GM->getWindowSize().x / 2.0f, GM->getWindowSize().y / 2), "PLAY GAME");
        bt->select(true);
        vectorOfButtons.push_back(bt);

        bt = new GraphicalElements::Button(TupleF(GM->getWindowSize().x / 2.0f, GM->getWindowSize().y / 2 + 100), "LEADERBOARD");
        vectorOfButtons.push_back(bt);

        bt = new GraphicalElements::Button(TupleF(GM->getWindowSize().x / 2.0f, GM->getWindowSize().y / 2 + 200), "SETTINGS");
        vectorOfButtons.push_back(bt);

        bt = new GraphicalElements::Button(TupleF(GM->getWindowSize().x / 2.0f, GM->getWindowSize().y / 2 + 300), "EXIT GAME");
        vectorOfButtons.push_back(bt);

        title.setTextInfo("Castle-");
        title.setFontSize(140);
        title.setTextColor(77.6, 68.2, 44.3);
        title.setTextAlignment(GraphicalElements::TextAlignment::center);

        title.setPosition(TupleF(GM->getWindowSize().x / 2.0f, 0.0f - title.getSize().y / 2));

        max = 3;
    }

    MainMenuState::~MainMenuState()
    {
    }

    void MainMenuState::update(float dt)
    {
        active = true;
        if (title.getPosition().y < 200)
            title.setPosition(TupleF(title.getPosition().x, title.getPosition().y + 1));
    }

    /* Menu operation to render all it's objects. */
    void MainMenuState::render()
    {
        updateView();
        back.render();
        for (it = vectorOfButtons.begin(); it != vectorOfButtons.end(); ++it)
            (*it)->render();
        title.render();
    }

    void MainMenuState::exec()
    {
        if (active)
        {
            active = false;
            switch (selected)
            {
            case 0:
                changeState(States::stateID::PLAYING);
                break;
            default:
                break;
            }
        }
    }

    void MainMenuState::resetState()
    {
        vectorOfButtons[selected]->select(false);
        selected = 0;
        vectorOfButtons[selected]->select(true);
        title.setPosition(TupleF(title.getPosition().x, 0.0f - title.getSize().y / 2));
    }

}