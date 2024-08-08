#include "Entities/Entity.hpp"

namespace Entities
{

    ID id;
    GraphicBodies::StaticBody *image;

    /*general info*/
    Coordinates::CoordF size;
    Coordinates::CoordF position;

    Entity::Entity(Coordinates::CoordF _position, ID _id) : size(),
                                                            position(_position),
                                                            id(_id),
                                                            image()
    {
        initialize();
    } // image vai ser inicializado na funçao initialize,

    Entity::~Entity()
    {
    }

    /*SETs*/
    void Entity::set_position(Coordinates::CoordF _position)
    {
        position = _position;
    }
    void Entity::set_size(Coordinates::CoordF _size)
    {
        size = _size;
    }
    /*GETs*/
    Coordinates::CoordF Entity::get_size()
    {
        return size;
    }
    Coordinates::CoordF Entity::get_position()
    {
        return position;
    }
    ID Entity::get_id()
    {
        return id;
    }
}
