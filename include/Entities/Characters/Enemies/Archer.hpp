#pragma once
#include "Entities/Characters/Enemies/Enemy.hpp"
#include "Entities/Projectiles/Arrow.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class Archer : public Enemy
            {
            private:
            public:
                Archer(TupleF position = TupleF(400.0f, 100.0f));

                ~Archer();
                void shoot();
                void atack();

                void update(const float dt);

                void initialize();

                void execute();

                void toDamage(Player *pP);

                void updateSprite(float dt);
            };

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
