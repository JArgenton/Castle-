#pragma once

#include "Control/Observer.hpp"

namespace Menus
{
    class Menu;
} // namespace Menus

namespace Control
{
    // controles inspirados na implementação do monitor Burda
    class MenuControl : public Observer
    {
    private:
        Menus::Menu *pMenu;

    public:
        MenuControl(Menus::Menu *pM = NULL);

        ~MenuControl();

        void notifyPressed(std::string key);

        void notifyReleased(std::string key);

        void setMenu(Menus::Menu *p);
    };

} // namespace Control