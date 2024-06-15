#include "Utilis/Coordinates/Coord.h"
using namespace Utilis;

namespace Entities{
    enum EntityType{
        empty = 0,
        PLAYER,
        ENEMY,
        PROJECTILE,
        PLATAFORM,
        ITEM,
    };

    class Entity{
        protected:
            Coordinates::CoordF position;
            Coordinates::CoordF size;

            EntityType type;
        public:
            Entity(Coordinates::CoordF position = Coordinates::CoordF(0.f, 0.f), Coordinates::CoordF size = Coordinates::CoordF(0.f, 0.f), EntityType type = empty);

            ~Entity();

            /*Position methods*/
            Coordinates::CoordF getPosition();
            void setPosition(Coordinates::CoordF position);

            /*Size methods*/
            Coordinates::CoordF getSize();
            void setSize(Coordinates::CoordF size);

            /*Type methods*/    
            EntityType getType();

            /*graphic manipulation*/
            virtual void render() = 0;
            virtual void update(float dt) = 0;   
            virtual void initilize() = 0;

            /*colision manager*/
             virtual void collide(Entity* other, Coordinates::CoordF intersection) = 0;








    };
}