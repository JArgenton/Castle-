#include "Control/MenuControl.hpp"
#include "Menus/PauseMenu.hpp"
#include "Menus/Menu.hpp"

namespace Control
{

    // controles de menu inspirados na implementação do monitor Burda

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
            pMenu->execute();

        if (key == "Escape")
            if (dynamic_cast<Menus::PauseMenu *>(pMenu) != nullptr)
                dynamic_cast<Menus::PauseMenu *>(pMenu)->initPause();
    }

    void MenuControl::notifyReleased(std::string key) {}

    void MenuControl::setMenu(Menus::Menu *p)
    {
        pMenu = p;
    }

} // namespace Control