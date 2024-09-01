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
                void initialize();
                void toDamage(Player *pP);
                void update(const float dt);
                void execute();
                void updateSprite(float dt);
            };
        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
