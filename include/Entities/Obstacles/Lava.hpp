#pragma once
#include "Entities/Obstacles/Obstacles.hpp"

namespace Entities
{
    namespace Obstacles
    {
        class Lava : public Obstacle
        {
        private:
            const int Maxdamage;
            float slowness;
            float damage;

        public:
            Lava(TupleF _position = TupleF(90.0f, 100.0f));
            ~Lava();
            void initialize();
            void update(float dt);
            void toObstruct(Entities::Characters::Character *pC);
        };

    } // namespace Obstacles

} // namespace Entities
