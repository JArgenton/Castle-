#pragma once
#include "Entities/Projectiles/Projectile.hpp"

namespace Entities
{
    namespace Projectiles
    {
        class Arrow : public Projectile
        {
        public:
            Arrow(TupleF _position);
            ~Arrow();
            void update(float dt);
            void initialize();
            const float getDamage();
            void setDirection(TupleF _direction);
            void collide(Entity *otherEntity, TupleF intersect);
            // void updateSprite(const float dt) override;
        };
    }

}