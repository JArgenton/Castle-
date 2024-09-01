#include "Entities/MovingEntity.hpp"

namespace Entities
{

    MovingEntity::MovingEntity(TupleF _position, ID id) : Entity(_position, id),
                                                          velocity(),
                                                          active(true),
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
    void MovingEntity::render()
    {
        sprite.render();
    }
    void MovingEntity::setActive(bool active)
    {
        active = active;
    }

    void MovingEntity::setFacing(bool direction)
    {
        if (direction)
        {
            body->setScale(-1, 1);
        }
        else
        {
            body->setScale(1, 1);
        }

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

        if (intersection.x > intersection.y)
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