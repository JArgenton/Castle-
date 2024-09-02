#include "Managers/InputManager.hpp"
#include "Control/Observer.hpp"
#include <iostream>

namespace Managers
{
    /*CLASSE INSPIRADA NA IMPLEMENTAÇAO DO MONITOR BURDA, MAS COM AS DEVIDAS MODIFICAÇOES*/

    InputManager *InputManager::instance = nullptr;

    InputManager *InputManager::getInstance()
    {
        if (instance == nullptr)
        {
            instance = new InputManager();
        }
        return instance;
    }

    // observer sempre recebe string, desacopla ele de sfml assim como qualquer classe filha de observer
    InputManager::InputManager()
    {
        keyMap[sf::Keyboard::A] = "A";
        keyMap[sf::Keyboard::B] = "B";
        keyMap[sf::Keyboard::C] = "C";
        keyMap[sf::Keyboard::D] = "D";
        keyMap[sf::Keyboard::E] = "E";
        keyMap[sf::Keyboard::F] = "F";
        keyMap[sf::Keyboard::G] = "G";
        keyMap[sf::Keyboard::H] = "H";
        keyMap[sf::Keyboard::I] = "I";
        keyMap[sf::Keyboard::J] = "J";
        keyMap[sf::Keyboard::K] = "K";
        keyMap[sf::Keyboard::L] = "L";
        keyMap[sf::Keyboard::M] = "M";
        keyMap[sf::Keyboard::N] = "N";
        keyMap[sf::Keyboard::O] = "O";
        keyMap[sf::Keyboard::P] = "P";
        keyMap[sf::Keyboard::Q] = "Q";
        keyMap[sf::Keyboard::R] = "R";
        keyMap[sf::Keyboard::S] = "S";
        keyMap[sf::Keyboard::T] = "T";
        keyMap[sf::Keyboard::U] = "U";
        keyMap[sf::Keyboard::V] = "V";
        keyMap[sf::Keyboard::W] = "W";
        keyMap[sf::Keyboard::X] = "X";
        keyMap[sf::Keyboard::Y] = "Y";
        keyMap[sf::Keyboard::Z] = "Z";
        keyMap[sf::Keyboard::Num1] = "1";
        keyMap[sf::Keyboard::Num2] = "2";
        keyMap[sf::Keyboard::Num3] = "3";
        keyMap[sf::Keyboard::Num4] = "4";
        keyMap[sf::Keyboard::Num5] = "5";
        keyMap[sf::Keyboard::Num6] = "6";
        keyMap[sf::Keyboard::Num7] = "7";
        keyMap[sf::Keyboard::Num8] = "8";
        keyMap[sf::Keyboard::Num9] = "9";
        keyMap[sf::Keyboard::Num0] = "0";
        keyMap[sf::Keyboard::Space] = "Space";
        keyMap[sf::Keyboard::Enter] = "Enter";
        keyMap[sf::Keyboard::Escape] = "Escape";
        keyMap[sf::Keyboard::BackSpace] = "BackSpace";
        keyMap[sf::Keyboard::Right] = "Right";
        keyMap[sf::Keyboard::Left] = "Left";
        keyMap[sf::Keyboard::Up] = "Up";
        keyMap[sf::Keyboard::Down] = "Down";
        keyMap[sf::Keyboard::LControl] = "Control";
        keyMap[sf::Keyboard::LShift] = "Shift";
        keyMap[sf::Keyboard::RControl] = "RControl";
        keyMap[sf::Keyboard::RShift] = "RShift";
        keyMap[sf::Keyboard::Hyphen] = "-";
        keyMap[sf::Keyboard::Tab] = "Tab";
    }

    InputManager::~InputManager()
    {
        objObserving.clear();
        keyMap.clear();
    }

    /* Subscribe a Observer to recieve a notification when something happens. */
    void InputManager::Attach(Control::Observer *pObserver)
    {
        objObserving.push_back(pObserver);
    }

    void InputManager::Detach(Control::Observer *pObserver)
    {
        objObserving.remove(pObserver);
    }

    /* Check for keys pressed and notify every Observer. */
    void InputManager::handleKeyPressed(sf::Keyboard::Key key)
    {
        for (it = objObserving.begin(); it != objObserving.end(); ++it)
            (*it)->notifyPressed(getKeyasString(key));
    }

    /* Check for keys pressed and notify every Observer. */
    void InputManager::handleKeyReleased(sf::Keyboard::Key key)
    {
        for (it = objObserving.begin(); it != objObserving.end(); ++it)
            (*it)->notifyReleased(getKeyasString(key));
    }

    std::string InputManager::getKeyasString(sf::Keyboard::Key key)
    {
        return keyMap[key] == "" ? "Unknown" : keyMap[key];
    }

} // namespace Managers