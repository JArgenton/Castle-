#include "Entities/Entity.hpp"

namespace Entities
{
    Entity::Entity(TupleF _position, ID _id) : Ent(),
                                               id(_id)
    {

        setPosition(_position);
    }

    Entity::~Entity()
    {
    }

    /*SETs*/
    void Entity::setPosition(TupleF _position)
    {
        body->setPosition(sf::Vector2f(_position.x, _position.y));
    }
    void Entity::setSize(float height, float width)
    {

        body->setSize(sf::Vector2f(height, width));
        setOrigem(height, width);
    }

    /*GETs*/
    TupleF Entity::getSize()
    {
        return TupleF(body->getSize().x, body->getSize().y);
    }
    TupleF Entity::getPosition()
    {
        float x = body->getPosition().x;
        float y = body->getPosition().y;
        TupleF pos = TupleF(x, y);
        return pos;
    }
    ID Entity::getId()
    {
        return id;
    }
}
