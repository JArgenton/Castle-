#ifndef _MOVINGENTITY_H_
#define _MOVINGENTITY_H_
#pragma once 
#include "Entity.h"


namespace Entities{

    class MovingEntity : public Entity
    {
        protected:
            
            // Animation


            Coordinates::CoordF velocity;
            bool active;
            bool facing_right;


        public:
            MovingEntity(Coordinates::CoordF position = Coordinates::CoordF(0.f, 0.f), Coordinates::CoordF size = Coordinates::CoordF(0.f, 0.f), EntityType type = empty, Coordinates::CoordF velocity = Coordinates::CoordF(0.f, 0.f));
            virtual ~MovingEntity();

            /*morre aqui*/
            virtual void render() override{}

            virtual void update(const float dt) = 0;
            virtual void initilize() = 0;

            virtual void collide(Entity* other, Coordinates::CoordF intersection) = 0;
            virtual void moveOnColision(const Coordinates::CoordF intersection, Entity* other) = 0;


            const bool isActive() const;

            const bool isFacingRight() const;
            void setFacingRight(const bool right);
            void setFacingRight();


            void setActive(const bool active);

            void setVelocity(const Coordinates::CoordF velocity);
            Coordinates::CoordF getVelocity();



    };
}
#endif