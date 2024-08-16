#include "Entities/StaticEntity.hpp"

namespace Entities
{

    StaticEntity::StaticEntity(Coordinates::CoordF _position, ID _id) : Entity(_position, _id),
                                                                        image()
    {
    }
    StaticEntity::~StaticEntity()
    {
    }
    void StaticEntity::render()
    {
        image.render();
    }

} // fim namespace Entities