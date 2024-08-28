#pragma once

#include "Menus/Menu.hpp"
#include "States/State.hpp"

namespace States
{
    class Jogo;
}

namespace Menus
{

    class MainMenuState : public Menu, public States::State
    {
    private:
        States::Jogo *pJogo;
        GraphicalElements::Text title;

    public:
        MainMenuState(States::Jogo *pG = nullptr);

        ~MainMenuState();

        void update(const float dt);

        void render();

        void resetState();

        void execute();
    };

}