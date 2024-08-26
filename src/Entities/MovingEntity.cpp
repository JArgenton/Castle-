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
    TupleF MovingEntity::getVelocity()
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

    void MovingEntity::moveOnColision(Entity *other, TupleF intersection)
    {
        TupleF pos = getPosition();
        TupleF otherPos = other->getPosition();

        if (intersection.x < intersection.y)
        {
            if (pos.x < otherPos.x)
            {
                body->move(intersection.x, 0);
            }
            else
            {
                body->move(-intersection.x, 0);
            }
            velocity.x = 0.0f;
        }
        else
        {
            if (pos.y < otherPos.y)
            {
                body->move(0, intersection.y);
            }
            else
            {
                body->move(0, -intersection.y);
            }
            velocity.y = 0.0f;
        }
    }
}