#include "Entities/Characters/Enemies/Enemy.hpp"
#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Characters/Player.hpp"

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
                    cout << "ERRO player nulo em  Enemy::setpPlayer." << endl;
                    exit(1);
                }
                pPlayer = pP;
            }

            TupleF Enemy::getPlayerPosition()
            {
                if (!pPlayer)
                {
                    cout << "ERRO player nulo em getPlayerPosition" << endl;
                    exit(1);
                }
                return pPlayer->getPosition();
            }

            void Enemy::receiveDamage(const int damage)
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
            }

            void Enemy::collide(Entity *otherEntity, TupleF intersect)
            {
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
                        receiveDamage(10); // player ainda não tem arma
                    }
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
                }
                default:
                    break;
                }
            }

        }
    }
}