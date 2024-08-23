#pragma once
<<<<<<< HEAD
#include "Entities/Characters/Player.hpp"
=======

#include "Entities/Characters/Character.hpp"
>>>>>>> ComEnemies

namespace Entities
{
    namespace Characters
    {
<<<<<<< HEAD
=======

        class Player;

>>>>>>> ComEnemies
        namespace Enemies
        {
            class Enemy : public Character
            {
<<<<<<< HEAD
            private:
                Player *pPlayer;

            protected:
                float playerDistance;

            public:
                Enemy(TupleF _position);
                virtual ~Enemy();
                virtual void collide(Entity *other, TupleF intersec) = 0;
                /*visuals*/
                virtual void initialize() = 0; // carrega as texturas
                virtual void update(const float dt) = 0;
                virtual void execute() = 0;
            };

        }
    }
=======
            protected:
                float playerDistance;
                const unsigned int points;
                Player *pPlayer;

            public:
                Enemy(TupleF _position = TupleF(400.0f, 100.0f),
                      ID id = empty,
                      int life = 1,
                      Entities::Characters::Player *pP = nullptr,
                      const float atkCooldown = 0.0f,
                      const float atkTime = 0.0f,
                      unsigned int points = 100);

                virtual ~Enemy();

                void setpPlayer(Player *pP);

                TupleF getPlayerPosition();

                void receiveDamage(const int damage);

                virtual void update(const float dt) = 0;

                virtual void initialize() = 0;

                virtual void collide(Entity *otherEntity, TupleF intersec);

                virtual void updateSprite(const float dt) = 0;
            };
        } // namespace Enemies

    } // namespace Characters

>>>>>>> ComEnemies
}