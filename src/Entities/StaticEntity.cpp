#include "Entities/StaticEntity.h"

namespace Entities{
    StaticEntity::StaticEntity(Coordinates::CoordF position, Coordinates::CoordF size,EntityType type):
        Entity(position, size, type)
    { }
    StaticEntity::~StaticEntity(){
    }

    void StaticEntity::render(){
        printf("rendering");
        /*TODO*/
       }
}