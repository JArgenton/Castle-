#include "Entities/StaticEntity.hpp"

namespace Entities
{
    List::EntityList Entities::StaticEntity::StaticEntities;

    StaticEntity::StaticEntity(TupleF _position, ID _id) : Entity(_position, _id)
    {
    }
    StaticEntity::~StaticEntity()
    {
    }
} // fim namespace Entities