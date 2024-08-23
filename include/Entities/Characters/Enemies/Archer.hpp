#pragma once
#include "Entities/Characters/Enemies/Enemy.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class Archer : public Enemy
            {
            private:
                static std::string texturepath;

            public:
                Archer(TupleF _position);
                ~Archer();
                void collide(Entity *other, TupleF intersec);
                void initialize();
                void update(const float dt);
                void execute();
            };
        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
