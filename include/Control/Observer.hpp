#pragma once

#include "Managers/InputManager.hpp"

namespace Control
{

    // Classe base para os observadores Inspirada na implementação do monitor Burda
    class Observer
    {
    private:
        Managers::InputManager *pIM;

    public:
        Observer();

        virtual ~Observer();

        // -------virtuais puros---------------------
        virtual void notifyPressed(std::string key) = 0;

        virtual void notifyReleased(std::string key) = 0;
    };

} // namespace Control