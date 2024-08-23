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
            public:
                Archer(TupleF position = TupleF(0.0f, 0.0f), Player *pP = nullptr);

                ~Archer();

                void update(const float dt);

                void initialize();

                // void updateSprite(const float dt);
            };

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
