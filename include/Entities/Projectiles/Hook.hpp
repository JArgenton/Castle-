#pragma once
#include "Entities/Projectiles/Projectile.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities
{
    namespace Projectiles
    {
        class Hook : public Projectile
        {
        public:
            Hook(TupleF _position);
            ~Hook();
            void update(float dt);
            void initialize();
            void setDirection(TupleF _direction);
            void collide(Entity *otherEntity, TupleF intersect);
            void hook(Entities::Characters::Player *pP);
            // void updateSprite(const float dt) override;
        };
    }

}