#include "Managers/EventsManager.hpp"

namespace Managers
{
    // Classe inspirada na implementação do monitor Burda para gerenciador de eventos
    /* ---------------------------------Singleton------------------------------------------ */
    EventsManager *EventsManager::instance = nullptr;

    EventsManager *EventsManager::getInstance()
    {
        if (instance == nullptr)
        {
            instance = new EventsManager();
        }
        return instance;
    }

    EventsManager::EventsManager() : pGraphicM(Managers::Graphics::get_instance()),
                                     pInputM(Managers::InputManager::getInstance()),
                                     pWindow(nullptr)
    {
        if (pGraphicM != nullptr)
            pWindow = pGraphicM->getWindow();
    }

    /* --------------------------------------------------------------------------------- */

    EventsManager::~EventsManager()
    {
        pGraphicM = nullptr;
        pInputM = nullptr;
        pWindow = nullptr;
    }

    void EventsManager::pollEvents()
    {
        sf::Event event;

        while (pWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                pGraphicM->closeWindow();
            if (event.type == sf::Event::KeyPressed)
                pInputM->handleKeyPressed(event.key.code);
            if (event.type == sf::Event::KeyReleased)
                pInputM->handleKeyReleased(event.key.code);
        }
    }

} // namespace Managers