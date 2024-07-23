#include "Entities/Entity.hpp"

namespace Entities{

        ID id;
        GraphicBodies::StaticBody* image;

        
        /*general info*/
        Coordinates::CoordF size;
        Coordinates::CoordF position;

            Entity::Entity(Coordinates::CoordF psize,
            Coordinates::CoordF pposition,
            ID id):
            size(psize),
            position(pposition),
            id(id),
            image() { } //image vai ser inicializado na funçao initialize, 

            Entity::~Entity(){
                image = nullptr;
            }

            /*SETs*/
            void set_position(Coordinates::CoordF pposition){
                position = pposition;
            }
            void Entity::set_size(Coordinates::CoordF psize){
                size = psize;
            }
            /*GETs*/
            Coordinates::CoordF Entity::get_size(){
                return size;
            }
            Coordinates::CoordF Entity::get_position(){
                return position;
            }
            ID Entity::get_id(){
                return id;
            }
}
