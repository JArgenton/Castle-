#pragma once
#include "Entities/Characters/Enemies/Enemy.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class EliteKnight : public Enemy
            {
            private:
                static std::string texturepath;
                float grabTimmer;
                float grabCooldown;

                float hitTimmer;
                float hitLimit;
                bool flagIsHitting;

            public:
                EliteKnight(TupleF _position);

                ~EliteKnight();

                void initialize();

                bool getIsHitting();
                float getHitTimmer();
                float getHitLimit();
                float getGrabTimmer();
                float getGrabCooldown();

                void setIsHitting(bool _isHitting);
                void setGrabTimmer(float _grabTimmer);
                void setGrabCooldown(float _grabCooldown);
                void setHitTimmer(float _hitTimmer);
                void setHitLimit(float _hitLimit);

                void update(const float dt);

                void shoot();

                void execute();

                void incrementAtkTimer(const float dt);
                void atack();

                void toDamage(Player *pP);

                bool canGrab();
                void updateSprite(float dt);
            };
        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
