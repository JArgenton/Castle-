#include "Entities/MovingEntity.hpp"

namespace Entities
{

    MovingEntity::MovingEntity(TupleF _position, ID id) : Entity(_position, id),
                                                          velocity(),
                                                          active(false),
                                                          facingLeft(false)
    {
    }

    MovingEntity::~MovingEntity()
    {
    }

    /*SETs*/
    void MovingEntity::set_velocity(TupleF pvelocity)
    {
        velocity = pvelocity;
    }
    void MovingEntity::setFacing(bool direction)
    {
        facingLeft = direction;
    }

    /*GETs*/
    TupleF MovingEntity::get_velocity()
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