#include "Entities/Characters/Enemies/Enemy.hpp"
#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Characters/Player.hpp"

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
            }

            Enemy::~Enemy()
            {
                pPlayer = nullptr;
            }

            void Enemy::setPlayer(Entities::Characters::Player *pP)
            {
                if (!pP)
                {
                    exit(1);
                }
                pPlayer = pP;
            }

            TupleF Enemy::getPlayerPosition()
            {
                if (!pPlayer)
                {
                    exit(1);
                }
                return pPlayer->getPosition();
            }
            float Enemy::getPlayerDistance()
            {
                return playerDistance;
            }

            void
            Enemy::updatePlayerDistance()
            {
                TupleF pos = getPosition();
                TupleF pPos = getPlayerPosition();
                playerDistance = sqrt(pow(pos.x - pPos.x, 2) + pow(pos.y - pPos.y, 2));
            }

            void Enemy::receiveDamage(const int damage)
            {
                if (canReciveDmg())
                {
                    health -= damage;
                    if (health <= 0)
                    {
                        active = false;
                        if (pPlayer != nullptr)
                        {
                            pPlayer->incrementPoints(points);
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
                    if (pPlayer != nullptr)
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
                    if (pPlayer)
                    {
                        if (pPlayer->isAtking())
                            receiveDamage(pPlayer->getAtkDamage());
                    }
                }
                break;
                default:
                    break;
                }
            }

        }
    }
}