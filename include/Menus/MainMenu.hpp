#pragma once

#include "Menus/Menu.hpp"
#include "States/State.hpp"

namespace Factories
{
    class Principal;
}

namespace Menus
{

    class MainMenuState : public Menu, public States::State
    {
    private:
        Factories::Principal *pPrin;
        GraphicalElements::Text title;

    public:
        MainMenuState(Factories::Principal *pP = nullptr);

        ~MainMenuState();

        void update(const float dt);

        void render();

        void resetState();

        void exec();
    };

}