#pragma once

#include "States/State.hpp"
#include "Menus/Menu.hpp"
#include "GraphElements/Text.hpp"

namespace Menus
{
    class LeaderBoard : public Menu, public States::State
    {
    private:
        std::vector<GraphicalElements::Text *> TotalPoints;
        std::vector<GraphicalElements::Text *>::iterator iter;

    public:
        LeaderBoard(States::StateMachine *pStateMachine = nullptr);

        ~LeaderBoard();

        void update(float dt);

        void render();

        void resetState();

        void execute();

        void build();
    };

} // namespace Menus
