#include "Entities/StaticEntity.hpp"

namespace Entities
{
    List::EntityList Entities::StaticEntity::StaticEntities;

    StaticEntity::StaticEntity(TupleF _position, ID _id) : Entity(_position, _id)
    {
        StaticEntities.add(static_cast<Entity *>(this));
    }
    StaticEntity::~StaticEntity()
    {
        Entity *aux = nullptr;
        aux = StaticEntities.remove(this);
        aux = nullptr;
    }
} // fim namespace Entities