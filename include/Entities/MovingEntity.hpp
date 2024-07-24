#include "Entity.hpp"

namespace Entities{
    class MovingEntity: public Entity
    {
     protected:
        /*geral info*/
        Coordinates::CoordF velocity;
       
        /*Flags*/
        bool active; 
        bool facingLeft;

     public:
            MovingEntity(Coordinates::CoordF psize = Coordinates::CoordF(0.0f, 0.0f),
            Coordinates::CoordF pposition = Coordinates::CoordF(0.0f, 0.0f),
            Coordinates::CoordF pvelocity = Coordinates::CoordF(0.0f, 0.0f),
            ID id = empty);

            ~MovingEntity();

            /*SETs*/
            void set_velocity(Coordinates::CoordF pvelocity);
            void setFacing(bool direction);

            /*GETs*/
            Coordinates::CoordF get_velocity();
            ID get_id();

            /*actions*/
            virtual void colide(Entity* other, Coordinates::CoordF intersec) = 0;

            /*visuals*/
            virtual void initialize() = 0; //carrega as texturas
            virtual void render() = 0; //atualiza posiçao da imagem

            /*Colisions*/
            virtual void moveOnColision(Entity* other) = 0; /*TODO classe Entity other*/

            /*conditions*/
            bool isActive();
            bool isFacingLeft();

            /*update*/
            virtual void update(const float dt) = 0;  
    };
}