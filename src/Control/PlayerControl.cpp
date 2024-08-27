#include "Control/PlayerControl.hpp"

namespace Control
{

    PlayerControl::PlayerControl(Entities::Characters::Player *pP) : Observer()
    {
        pPlayer = pP;
    }

    PlayerControl::~PlayerControl()
    {
        pPlayer = NULL;
    }

    void PlayerControl::notifyPressed(std::string key)
    {
        if (pPlayer == NULL)
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

    void PlayerControl::notifyReleased(std::string key) {}

    void PlayerControl::setPlayer(Entities::Characters::Player *pL)
    {
        pPlayer = pL;
    }

} // namespace Control