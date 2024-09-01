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
                float player1Distance;
                float player2Distance;
                int points;
                Player *pPlayer1;
                Player *pPlayer2;

            public:
                Enemy(TupleF _position, ID _id, int points = 10);

                virtual ~Enemy();

                void setPlayer(Player *pP);

                TupleF getPlayerPosition();
                bool isP1NearestPlayer();

                float updatePlayerDistance();

                virtual void toDamage(Player *) = 0;

                virtual void update(const float dt) = 0;

                virtual void initialize() = 0;

                virtual void collide(Entity *otherEntity, TupleF intersec);

                virtual void updateSprite(const float dt) = 0;
            };
        } // namespace Enemies

    } // namespace Characters

}