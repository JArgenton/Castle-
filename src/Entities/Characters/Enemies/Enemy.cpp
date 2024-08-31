#include "Entities/Characters/Enemies/Enemy.hpp"

#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Obstacles/Plataform.hpp"
#include "Entities/Obstacles/Trap.hpp"

#include "Entities/Characters/Player.hpp"
#include "Entities/Weapons/Sword.hpp"

#include <math.h>
namespace Entities
{
    using namespace Obstacles;

    namespace Characters
    {
        namespace Enemies
        {
            Enemy::Enemy(TupleF _position, ID _id, int _points) : Character(_position, _id),
                                                                  player1Distance(9999.0f),
                                                                  player2Distance(9999.0f),
                                                                  points(_points)

            {
                pPlayer1 = nullptr;
                pPlayer2 = nullptr;
            }

            Enemy::~Enemy()
            {
                pPlayer1 = nullptr;
                pPlayer2 = nullptr;
            }

            void Enemy::setPlayer(Entities::Characters::Player *pP)
            {
                if (pP)
                {
                    if (pPlayer1)
                    {
                        pPlayer2 = pP;
                    }
                    else
                    {
                        pPlayer1 = pP;
                    }
                }
            }

            TupleF Enemy::getPlayerPosition()
            {
                if (pPlayer2)
                {

                    if (pPlayer2->getFullyCreated() && !isP1NearestPlayer())
                    {
                        return pPlayer2->getPosition();
                    }
                }
                if (pPlayer1)
                {
                    return pPlayer1->getPosition();
                }
            }

            bool Enemy::isP1NearestPlayer()
            {
                if (!pPlayer2->getFullyCreated() || !pPlayer2->isActive())
                {
                    return true;
                }
                else if (!pPlayer1->isActive())
                {
                    return false;
                }
                else
                {
                    if (player1Distance < player2Distance)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            ID Enemy::getTargetPlayerId()
            {
                updatePlayerDistance();

                if (player1Distance < player2Distance)
                {
                    return ID::PLAYER1;
                }
                else
                {
                    return ID::PLAYER2;
                }
            }
            float Enemy::updatePlayerDistance()
            {
                if (!pPlayer1 && pPlayer2)
                {
                    cout << "p1 morto" << endl;
                }
                else if (pPlayer1 || pPlayer2)
                {
                    TupleF pos = getPosition();
                    TupleF pPos1 = pPlayer1->getPosition();
                    if (pPlayer2->getFullyCreated())
                    {
                        TupleF pPos2 = pPlayer2->getPosition();
                        player2Distance = sqrt(pow(pos.x - pPos2.x, 2) + pow(pos.y - pPos2.y, 2));
                    }
                    else
                    {
                        player2Distance = 9999.0f;
                    }

                    player1Distance = sqrt(pow((pos.x - pPos1.x), 2) + pow((pos.y - pPos1.y), 2));

                    return player1Distance < player2Distance ? player1Distance : player2Distance;

                    /* cout << "pos inimigo  ->>  " << pos.x << "  /  " << pos.y << endl;
                     cout << "pos p1  ->>  " << pPos1.x << "  /  " << pPos1.y << endl;
                     cout << "distancia -->" << player1Distance << endl;*/
                }
            }

            void Enemy::collide(Entity *otherEntity, TupleF intersect)
            {
                ID otherID = otherEntity->getId();

                switch (otherID)
                {
                case ID::PLAYER1:
                {
                    if (pPlayer1)
                    {
                        moveOnColision(otherEntity, intersect);
                        reciveDmg(25);
                    }
                    break;
                }
                case ID::PLAYER2:
                {
                    if (pPlayer2)
                    {
                        moveOnColision(otherEntity, intersect);
                        reciveDmg(10);
                    }
                    break;
                }
                case ID::WEAPON:
                {
                    Player *owner = dynamic_cast<Weapons::Sword *>(otherEntity)->getOwner();
                    if (owner->isAtking())
                    {
                        reciveDmg(owner->getAtkDamage());
                        isTraped(1.0f);
                        if (facingLeft)
                            set_velocity(TupleF(50.0f, -50.0f));
                        else
                        {
                            set_velocity(TupleF(-50.0f, -50.0f));
                        }
                    }
                    break;
                }
                case ID::PLATAFORM:
                {
                    moveOnColision(otherEntity, intersect);
                    static_cast<Plataform *>(otherEntity)->toObstruct(this);
                    break;
                }
                case ID::LAVA:
                {
                    moveOnColision(otherEntity, intersect);
                    static_cast<Lava *>(otherEntity)->toObstruct(this);
                    break;
                }
                case ID::TRAP:
                {
                    moveOnColision(otherEntity, intersect);
                    static_cast<Trap *>(otherEntity)->toObstruct(this);
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
}
