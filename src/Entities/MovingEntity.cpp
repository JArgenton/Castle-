#include "Entities/MovingEntity.hpp"

namespace Entities
{

    MovingEntity::MovingEntity(Coordinates::CoordF _position, ID id) : Entity(_position, id),
                                                                       velocity(),
                                                                       active(false),
                                                                       facingLeft(false)
    {
    }

    MovingEntity::~MovingEntity()
    {
    }

    /*SETs*/
    void MovingEntity::set_velocity(Coordinates::CoordF pvelocity)
    {
        velocity = pvelocity;
    }
    void MovingEntity::setFacing(bool direction)
    {
        facingLeft = direction;
    }

    /*GETs*/
    Coordinates::CoordF MovingEntity::get_velocity()
    {
        return velocity;
    }

    /*conditions*/
    bool MovingEntity::isActive()
    {
        return active;
    }
    bool MovingEntity::isFacingLeft()
    {
        return facingLeft;
    }
    void MovingEntity::initialize()
    {
    }
}