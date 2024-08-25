#pragma once

#include "Control/MenuControl.hpp"
#include "GraphElements/Button.hpp"
#include "GraphElements/StaticAnimation.hpp"
#include <vector>

namespace Menus
{

    class Menu
    {
    protected:
        std::vector<GraphicalElements::Button *> vectorOfButtons;
        std::vector<GraphicalElements::Button *>::iterator it;
        int selected;
        int min;
        int max;
        Control::MenuControl control;
        bool active;
        GraphicalElements::StaticAnimation back;

    public:
        Menu();

        virtual ~Menu();

        virtual void exec() = 0;

        void updateView();

        void selectDown();

        void selectUp();
    };

} // namespace Menus