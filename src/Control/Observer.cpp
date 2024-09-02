#include "Control/Observer.hpp"

namespace Control
{
    // classe baseada na implementação do monitor Burda
    Observer::Observer()
    {
        pIM = Managers::InputManager::getInstance();
        pIM->Attach(this);
    }

    Observer::~Observer()
    {
        pIM->Detach(this);
    }

} // namespace Control