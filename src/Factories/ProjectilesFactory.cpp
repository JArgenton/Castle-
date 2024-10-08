#include "Entities/Projectiles/Arrow.hpp"
#include "Factories/ProjectilesFactory.hpp"
#include "Entities/Projectiles/Hook.hpp"

namespace Factories
{
    ProjectilesFactory::ProjectilesFactory() : Factories::EntityFactory()
    {
    }

    ProjectilesFactory::~ProjectilesFactory()
    {
        MovingEntities = nullptr;
    }
    Entity *ProjectilesFactory::FactoryMethood(TupleF _position, ID _id)
    {

        Entity *pE = nullptr;
        switch (_id)
        {
        case ARROW:
        {
            pE = new Entities::Projectiles::Arrow(_position);
            break;
        }
        case HOOK:
        {
            pE = new Entities::Projectiles::Hook(_position);
            break;
        }
        default:
            break;
        }

        if (pE)
        {

            pE->initialize();
        }

        return pE;
    }
} // namespace Factories