#pragma once

#include <Managers/GraphicManager.hpp>
#include <list>
#include <map>
#include <string>

namespace Control
{
    class Observer;
} // namespace Control

namespace Managers
{

    class InputManager
    {
    private:
        std::list<Control::Observer *> objObserving;

        std::list<Control::Observer *>::iterator it;

        std::map<sf::Keyboard::Key, std::string> keyMap;

        // ----------Padrao de projeto Singleton---------------------

        static InputManager *instance;

        InputManager();

        //-----------------------------------------------------------
    public:
        ~InputManager();

        static InputManager *getInstance();

        void Attach(Control::Observer *pObserver);

        void Detach(Control::Observer *pObserver);

        void handleKeyPressed(sf::Keyboard::Key key);

        void handleKeyReleased(sf::Keyboard::Key key);

        std::string getKeyasString(sf::Keyboard::Key key);
    };

} // namespace Managers