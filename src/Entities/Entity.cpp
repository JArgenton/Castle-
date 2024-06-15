#include "Entities/Entity.h"

namespace Entities{

Entity::Entity(Coordinates::CoordF position, Coordinates::CoordF size, EntityType Type):
    position(position),
    size(size)
    {
        type = Type; 
    }

Entity::~Entity(){ 

}

/*Position methods*/
Coordinates::CoordF Entity::getPosition(){
    return position;
}

void Entity::setPosition(Coordinates::CoordF position){
    this->position = position;
}

/*Size methods*/
Coordinates::CoordF Entity::getSize(){
    return size;
}

void Entity::setSize(Coordinates::CoordF size){
    this->size = size;
}

/*Type methods*/    
EntityType Entity::getType(){
    return type;
}
}