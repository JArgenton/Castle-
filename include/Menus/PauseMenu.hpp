#pragma once

#include "Menus/Menu.hpp"
#include "States/State.hpp"
#include "States/Level.hpp"

namespace States
{
    class Jogo;
}

namespace Menus
{
    class PauseMenu : public Menu, public States::State
    {
    private:
        States::Jogo *pJogo;
        GraphicalElements::Text title;
        States::Level *getCurrentLevel();

    public:
        PauseMenu(States::Jogo *pJ = nullptr);
        ~PauseMenu();
        void execute();
        void update(float dt);
        void render();
        void resetState();
        void initPause();
    };

}
