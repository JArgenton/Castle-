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
    void MovingEntity::moveOnColision(Entity *other, TupleF intersection)
    {
        TupleF aux = getPosition();
        if (intersection.x > intersection.y)
        {
            velocity.x = 0;
            if (other->getPosition().x < aux.x)
            {
                aux.x -= intersection.x;
                setPosition(aux);
            }
            else
            {
                aux.x += intersection.x;
                cout << aux.x << endl;

                setPosition(aux);
            }
        }
        else
        {
            velocity.y = 0;
            if (other->getPosition().y < aux.y)
            {
                aux.y -= intersection.y;
                setPosition(aux);
            }
            else
            {
                aux.y += intersection.y;
                setPosition(aux);
            }
        }
    }
}