#pragma once 
#include "Entities/MovingEntity.h"

namespace Entities{

namespace Characters{
    
    class Character : public MovingEntity{

        protected:
            int health;

        public:
            Character(Coordinates::CoordF position = Coordinates::CoordF(0.f, 0.f), Coordinates::CoordF size = Coordinates::CoordF(0.f, 0.f), EntityType id = empty, int health = 100);
            ~Character();

            const int getHealth() const;
            void reciveDemage(const int damage);

            virtual void collide(const Entity* other, Coordinates::CoordF intersection);

            virtual void update() = 0; //atualizara a açao do personagem, kovendo-o etc...
            virtual void updateSprite() = 0; // sera chamada por update, apenas fara a animaçao da açaõ do personagem
            virtual void reciveDamage(const int damage);

             virtual void render(); //desenha o personagem na tela
            virtual void initilize() = 0;

            virtual void collide(Entity* other, Coordinates::CoordF intersection) = 0;
            virtual void moveOnColision(const Coordinates::CoordF intersection, Entity* other) = 0;



    };  // class Character
}
}