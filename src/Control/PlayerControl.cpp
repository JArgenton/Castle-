#include "Control/PlayerControl.hpp"

namespace Control
{
    using namespace States;

    PlayerControl::PlayerControl(Entities::Characters::Player *pP) : Observer()
    {
        pPlayer1 = pP;
        pPlayer2 = nullptr;
    }

    PlayerControl::~PlayerControl()
    {
        pPlayer1 = NULL;
        pPlayer2 = NULL;
    }

    void PlayerControl::notifyPressed(std::string key)
    {
        if (!pPlayer1 || !pPlayer2)
        {
            cout << "um dos players esta nulo" << endl;
            exit(1);
        }
        if (key == "Space" && !pPlayer2->getFullyCreated())
        {
            pPlayer2->initialize();
            pPlayer2->setPosition(pPlayer1->getPosition());
        }

        if (key == "Up")
            pPlayer1->jump();

        if (key == "Down")
        {
            pPlayer1->atack();
        }
        if (key == "Left")
        {
            pPlayer1->walk(true);
        }
        if (key == "Right")
        {
            pPlayer1->walk(false);
        }

        if (pPlayer2->getFullyCreated())
        {

            if (key == "W")
                pPlayer2->jump();

            if (key == "S")
            {
                pPlayer2->atack();
            }
            if (key == "A")
            {
                pPlayer2->walk(true);
            }
            if (key == "D")
            {
                pPlayer2->walk(false);
            }
        }
    }

    void PlayerControl::notifyReleased(std::string key)
    {

        if (!pPlayer1 || !pPlayer2)
        {
            cout << "um dos players esta nulo" << endl;
        }

        if (key == "Left")
        {
            if (pPlayer1->getVelocity().x < 0)
            {
                pPlayer1->stop();
            }
        }
        if (key == "Right")
        {
            if (pPlayer1->getVelocity().x > 0)
            {
                pPlayer1->stop();
            }
        }

        if (pPlayer2->getFullyCreated())
        {

            if (key == "D")
            {
                pPlayer2->stop();
            }
            if (key == "A")
            {
                pPlayer2->stop();
            }
        }
    }
    void PlayerControl::setPlayer(Entities::Characters::Player *pL)
    {
        if (pPlayer1)
        {
            pPlayer2 = pL;
        }
        else
        {
            pPlayer1 = pL;
        }
    }

} // namespace Control