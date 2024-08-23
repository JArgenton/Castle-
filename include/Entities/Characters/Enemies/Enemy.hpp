#pragma once
#include "Entities/Characters/Player.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            class Enemy : public Character
            {
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
}