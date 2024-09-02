#pragma once

#include "Menus/Menu.hpp"
#include "States/State.hpp"

namespace States
{
    class Game;
}

namespace Menus
{

    class MainMenuState : public Menu, public States::State
    {
    private:
        States::Game *pJogo;
        GraphicalElements::Text title;

    public:
        MainMenuState(States::Game *pG = nullptr);

        ~MainMenuState();

        void update(const float dt);

        void render();

        void resetState();

        void execute();
    };

}