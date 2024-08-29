#pragma once
#include "Entities/Characters/Enemies/Enemy.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class BigBoss : public Enemy
            {
            private:
                static std::string texturepath;
                float grabTimmer;
                float grabCooldown;

                float hitTimmer;
                float hitLimit;
                bool flagIsHitting;

            public:
                BigBoss(TupleF _position);

                ~BigBoss();

                void initialize();

                void update(const float dt);

                void shoot();

                void execute();

                void incrementAtkTimer(const float dt);
                void atack();

                void toDamage(Player *pP);

                bool canGrab();
            };
        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
