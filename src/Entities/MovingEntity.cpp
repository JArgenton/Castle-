#include "Entities/MovingEntity.h"


namespace Entities{

    MovingEntity::MovingEntity(Coordinates::CoordF position, Coordinates::CoordF size, EntityType type, Coordinates::CoordF velocity ):
        Entity(position, size, type),
        velocity(velocity),
        active(true),
        facing_right(true)
    { }

    MovingEntity::~MovingEntity() { }

    const bool MovingEntity::isActive() const{
        return active;
    }

    const bool MovingEntity::isFacingRight() const{
        return facing_right;
    }

    void MovingEntity::setFacingRight(const bool right){
        facing_right = right;
    }
    void MovingEntity::setFacingRight(){
        facing_right = velocity.x > 0.0f ? false : true;
    }


    void MovingEntity::setActive(const bool active){
        this->active = active;
    }

    void MovingEntity::setVelocity(const Coordinates::CoordF velocity){
        this->velocity = velocity;
    }
    Coordinates::CoordF MovingEntity::getVelocity(){

    }
}