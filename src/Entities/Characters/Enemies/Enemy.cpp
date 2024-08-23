#include "Entities/Characters/Enemies/Enemy.hpp"

#include "Entities/Characters/Player.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            Enemy::Enemy(TupleF _position,
                         ID id,
                         int life,
                         Entities::Characters::Player *pP,
                         const float atkCooldown,
                         const float atkTime,
                         const unsigned int points) : Character(_position, id), pPlayer(pP), points(points)
            {
            }

            Enemy::~Enemy()
            {
                pPlayer = nullptr;
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

            void Enemy::setpPlayer(Entities::Characters::Player *pP)
            {
                if (!pP)
                {
                    cout << "ERRO player nulo em  Enemy::setpPlayer." << endl;
                    exit(1);
                }
                pPlayer = pP;
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
                switch (otherEntity->getId())
                {
                case ID::PLATAFORMA:
                {
                    moveOnColision(otherEntity, intersect);
                    break;
                }
                case ID::PLAYER:
                {
                    if (pPlayer != nullptr)
                    {
                        moveOnColision(otherEntity, intersect);
                        receiveDamage(10); // player ainda não tem arma, dessa forma o inimigo vai tomar o proprio dano que causaria ao player quando se encostarem
                    }
                }
                case ID::LAVA:
                {
                    moveOnColision(otherEntity, intersect);
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