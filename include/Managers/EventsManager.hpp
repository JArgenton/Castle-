#pragma once

#include "Managers/GraphicManager.hpp"
#include "Managers/InputManager.hpp"

namespace Managers
{

    class EventsManager
    {
    private:
        Graphics *pGraphicM;
        InputManager *pInputM;
        sf::RenderWindow *pWindow;

        //---------singleton----------
        static EventsManager *instance;
        EventsManager();

    public:
        ~EventsManager();

        static EventsManager *getInstance();

        void setGraphicManager();
        void setInput(InputManager *pIM);

        void pollEvents();
    };

} // namespace Managers