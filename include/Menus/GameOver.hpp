#pragma once

#include "Control/TextInput.hpp"
#include "GraphElements/Text.hpp"
#include "Menus/Menu.hpp"
#include "States/State.hpp"
#include "States/StateMachine.hpp"
#include "States/Level.hpp"

namespace Menus
{

    class GameOver : public Menu, public States::State
    {
    private:
        GraphicalElements::Text title;
        GraphicalElements::Text points;
        GraphicalElements::Text name;
        GraphicalElements::Text nameLabel;
        Control::TextInput input;
        int pointsToIncrement;
        States::Level *plvl;

    public:
        GameOver(States::StateMachine *pSM = nullptr, States::Level *plvl = nullptr);

        ~GameOver();

        void update(float dt);

        void render();

        void exec();

        void resetState();

        void writeIntoFile();

        void execute() override {}
    };

}