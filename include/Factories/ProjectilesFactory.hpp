#pragma once
#include "Factories/EntityFactory.hpp"
#include "Lists/EntityList.hpp"
namespace Factories
{
    class ProjectilesFactory : public EntityFactory
    {
    private:
        List::EntityList *MovingEntities;

    public:
        ProjectilesFactory();
        ~ProjectilesFactory();
        Entity *FactoryMethood(TupleF _position, ID _id);
    };

} // namespace Factories
