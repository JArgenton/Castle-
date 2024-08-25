#include "Control/MenuControl.hpp"
#include "Menus/Menu.hpp"

namespace Control
{

    MenuControl::MenuControl(Menus::Menu *pM) : Observer()
    {
        pMenu = pM;
    }

    MenuControl::~MenuControl()
    {
        pMenu = NULL;
    }

    void MenuControl::notifyPressed(std::string key)
    {
        if (pMenu == NULL)
        {
            std::cout << "ERRO ponteiro nulo MenuControl::notify()." << std::endl;
            exit(1);
        }

        if (key == "Down")
            pMenu->selectDown();
        if (key == "Up")
            pMenu->selectUp();
        if (key == "Enter")
            pMenu->exec();
        }

    void MenuControl::notifyReleased(std::string key) {}

    void MenuControl::setMenu(Menus::Menu *p)
    {
        pMenu = p;
    }

} // namespace Control