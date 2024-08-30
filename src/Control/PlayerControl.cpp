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

        if (!pStateM)
        {
            cout << "maquina de estados nula ???????" << endl;
            exit(1);
        }

        if (pStateM->getStateID() == stateID::FASE)
        {

            if (!pPlayer1 || !pPlayer2)
            {
                cout << "players estao nulos" << endl;
                exit(1);
            }

            if (key == "Space")
            {
                if (!pPlayer2->getFullyCreated())
                {
                    pPlayer2->initialize();
                    pPlayer2->setPosition(pPlayer1->getPosition());
                }
                else if (!pPlayer1->getFullyCreated())
                {
                    pPlayer1->initialize();
                    pPlayer1->setPosition(pPlayer2->getPosition());
                }
            }
            if (pPlayer1->isActive())
            {
                if (key == "Up")
                {
                    pPlayer1->jump();
                }

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
            }
            if (pPlayer2->getFullyCreated() && pPlayer2->isActive())
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
    }

    void PlayerControl::notifyReleased(std::string key)
    {

        if (!pStateM)
        {
            cout << "maquina de estados nula ???????" << endl;
            exit(1);
        }
        if (pStateM->getStateID() == stateID::FASE)
        {
            if (!pPlayer1 && !pPlayer2)
            {
                cout << "um dos players esta nulo" << endl;
                exit(1);
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

    void PlayerControl::setMachine(StateMachine *pSTM)
    {
        pStateM = pSTM;
    }

} // namespace Control