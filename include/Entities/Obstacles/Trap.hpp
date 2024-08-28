#pragma once

#include "Entities/Obstacles/Obstacles.hpp"

namespace Entities
{
    namespace Obstacles
    {
        class Trap : public Obstacle
        {
        private:
            float reloadTimmer;
            int damage;
            float reloadCooldown;
            float trapDuration;

        public:
            Trap(TupleF _position = TupleF(90.0f, 100.0f));
            ~Trap();
            void initialize();
            bool operational();
            void update(float dt);
            void toObstruct(Characters::Character *pC);
        };
    } // namespace Obstacles

} // namespace Entities
