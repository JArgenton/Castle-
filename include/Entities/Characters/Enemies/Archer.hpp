#pragma once

#include "Entities/Characters/Enemies/Enemy.hpp"
#include "Entities/Weapons/Projectile.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class Archer : public Enemy
            {
            private:
                std::vector<Projectile> projectiles; // Lista de projéteis
                void addProjectile(const Projectile &projectile);
                const std::vector<Projectile> &getProjectiles() const;
                float timer;

            public:
                Archer(TupleF position = TupleF(400.0f, 100.0f), Player *pP = nullptr);

                ~Archer();

                void shoot();

                void update(const float dt);

                void initialize();

                void updateSprite(const float dt);

                void execute();

                // void updateSprite(const float dt);
            };

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
