#pragma once

#include "Entities/MovingEntity.hpp"

namespace Entities
{
    namespace Projectiles
    {
        class Projectile : public MovingEntity
        {
        protected:
            int damage;

        public:
            Projectile(TupleF _position, ID _id);
            virtual ~Projectile();
            virtual void update(float dt) = 0;
            void setDamage(const int _damage);
            const int getDamage();
            virtual void initialize() = 0;
            virtual void collide(Entity *otherEntity, TupleF intersect);
            void execute() override {}
            // void updateSprite(const float dt) override;
        };
    }

}