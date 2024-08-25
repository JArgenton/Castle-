#include "Control/Observer.hpp"

namespace Control
{

    Observer::Observer()
    {
        this->pIM = Managers::InputManager::getInstance();
        pIM->Attach(this);
    }

    Observer::~Observer()
    {
        pIM->Detach(this);
    }

} // namespace Control