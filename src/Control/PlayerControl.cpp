#include "Control/PlayerControl.hpp"

namespace Control
{
    using namespace States;

    PlayerControl::PlayerControl(Entities::Characters::Player *pP) : Observer()
    {
        pPlayer = pP;
    }

    PlayerControl::~PlayerControl()
    {
        pPlayer = nullptr;
    }

    void PlayerControl::notifyPressed(std::string key)
    {

        if (pPlayer == nullptr)
        {
            std::cout << "ERRO ponteiro nulo PlayerControl::notify()." << std::endl;
            exit(1);
        }

        if (key == "Up")
            pPlayer->jump();
        if (key == "Space")
        {
            pPlayer->atack();
        }
        if (key == "Left")
        {
            pPlayer->walk(true);
        }
        if (key == "Right")
        {
            pPlayer->walk(false);
        }
    }

    void PlayerControl::notifyReleased(std::string key)
    {
        if (key == "Left")
        {
            if (pPlayer->getVelocity().x < 0)
            {
                pPlayer->stop();
            }
        }
        if (key == "Right")
        {
            if (pPlayer->getVelocity().x > 0)
            {
                pPlayer->stop();
            }
        }
    }

    void PlayerControl::setPlayer(Entities::Characters::Player *pL)
    {
        pPlayer = pL;
    }

} // namespace Control