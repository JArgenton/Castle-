#include "Entities/Characters/Enemies/Enemy.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {

            Player *pPlayer;

            Enemy::Enemy(TupleF _position) : Character(_position),
                                             playerDistance(0.0f)
            {
            }
            Enemy::~Enemy()
            {
                active = false;
                pPlayer = nullptr;
            }

        }
    }
}