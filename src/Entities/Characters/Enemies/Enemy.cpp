#include "Entities/Characters/Enemies/Enemy.hpp"
#include "Entities/Obstacles/Lava.hpp"
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
                    pPlayer1 = pP;
                }
            }

            TupleF Enemy::getPlayerPosition()
            {

                if (pPlayer2 && !isP1NearestPlayer())
                {
                    return pPlayer2->getPosition();
                }

                return pPlayer1->getPosition();
            }

            float Enemy::getPlayerDistance()
            {

                return player1Distance < player2Distance ? player1Distance : player2Distance;
            }
            bool Enemy::isP1NearestPlayer()
            {

                return player1Distance < player2Distance;
            }

            void
            Enemy::updatePlayerDistance()
            {
                TupleF pos = getPosition();
                TupleF pPos1 = pPlayer1->getPosition();
                TupleF pPos2 = pPlayer2->getPosition();
                player1Distance = sqrt(pow(pos.x - pPos1.x, 2) + pow(pos.y - pPos1.y, 2));
                player1Distance = sqrt(pow(pos.x - pPos2.x, 2) + pow(pos.y - pPos2.y, 2));
            }

            void Enemy::receiveDamage(const int damage)
            {

                if (canReciveDmg())
                {
                    cout << damage << endl;

                    health -= damage;
                    if (health <= 0)
                    {
                        active = false;
                        if (pPlayer1 != nullptr)
                        {
                            pPlayer1->incrementPoints(points);
                        }
                    }
                    dmgTimer = 0;
                }
            }

            void Enemy::collide(Entity *otherEntity, TupleF intersect)
            {
                if (otherEntity->getId() != ID::WEAPON)
                    moveOnColision(otherEntity, intersect);

                switch (otherEntity->getId())
                {
                case ID::PLATAFORMA:
                {
                    break;
                }
                case ID::PLAYER1:
                {
                    if (pPlayer1)
                    {
                        moveOnColision(otherEntity, intersect);
                        receiveDamage(10);
                    }
                    break;
                }
                case ID::PLAYER2:
                {
                    if (pPlayer2)
                    {
                        moveOnColision(otherEntity, intersect);
                        receiveDamage(10);
                    }
                    break;
                }
                case ID::LAVA:
                {
                    moveOnColision(otherEntity, intersect);

                    Lava *lava = dynamic_cast<Lava *>(otherEntity);
                    if (lava)
                    {
                        receiveDamage(lava->getDamage());
                    }
                    break;
                }
                case ID::ARMADILHA:
                {
                    break;
                }
                case ID::WEAPON:
                {
                    Player *owner = dynamic_cast<Weapons::Sword *>(otherEntity)->getOwner();
                    if (owner->isAtking())
                    {
                        receiveDamage(pPlayer2->getAtkDamage());
                    }

                    break;
                }
                default:
                    break;
                }
            }
        }
    }
}
