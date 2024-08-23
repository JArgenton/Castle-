#pragma once

#include "Entities/Characters/Character.hpp"

namespace Entities
{
    namespace Characters
    {

        class Player;

        namespace Enemies
        {
            class Enemy : public Character
            {
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

}