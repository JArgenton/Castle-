#pragma once
#include "Entities/Characters/Enemies/Enemy.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class Dumb : public Enemy
            {
            private:
                static std::string texturepath;

            public:
                Dumb(TupleF _position);
                ~Dumb();
                void collide(Entity *other, TupleF intersec);
                void initialize();
                void update(const float dt);
                void execute();
                void toDamage(Player *pP);
            };
        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
