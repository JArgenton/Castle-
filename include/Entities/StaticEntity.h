#pragma once 
#include "Entity.h"

namespace Entities{
    class StaticEntity : public Entity
    {
        protected:
        /*TODO*/
        //Animation
        public:
            StaticEntity(Coordinates::CoordF position = Coordinates::CoordF(0.f, 0.f), Coordinates::CoordF size = Coordinates::CoordF(0.f, 0.f),EntityType type = empty);
            virtual ~StaticEntity();

           void render() override;

            virtual void initilize() = 0;

            /*morrem aqui*/
            virtual void collide(Entity* other, Coordinates::CoordF intersection) override{}
            virtual void update(float dt) override{}   
    };
}