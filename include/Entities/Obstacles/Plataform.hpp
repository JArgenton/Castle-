#pragma once
#include "Entities/Obstacles/Obstacles.hpp"

namespace Entities
{
    namespace Obstacles
    {
        class Plataform : public Obstacle
        {
        private:
            bool fake;

        public:
            Plataform(TupleF _position = TupleF(80.0f, 100.0f));
            ~Plataform();
            void initialize();
            void update(float dt);
            void toObstruct(Entities::Characters::Character *pC);
        };

    } // namespace Obstacles

}