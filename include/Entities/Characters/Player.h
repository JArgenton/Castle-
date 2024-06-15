#pragma once
#include "Character.h"
#define PLAYER_SIZE_X 100.0f
#define PLAYER_SIZE_Y 100.0f


namespace Entities{
    namespace Characters{
            class Player: public Character
            {
            private:
                bool isPlayer1;
            public:

                Player(Coordinates::CoordF pos = Coordinates::CoordF(0.f, 0.f), bool isPlayer1 = true);

                ~Player();

                void initialize();

                void collide(Entity* other, Coordinates::CoordF intersection);
                virtual void moveOnColision(const Coordinates::CoordF intersection, Entity* other) = 0;

                void update(float dt);
                void updateSprite(float dt);

                //load all sprites
                virtual void initilize();
            };  

    }
}