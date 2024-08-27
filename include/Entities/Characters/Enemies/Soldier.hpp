#pragma once
#include "Entities/Characters/Enemies/Enemy.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class Soldier : public Enemy
            {
            private:
                static std::string texturepath;

            public:
                Soldier(TupleF _position);
                ~Soldier();
                void collide(Entity *other, TupleF intersec);
                void initialize();
                void toDamage(Player *pP);
                void update(const float dt);
                void execute();
            };
        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
