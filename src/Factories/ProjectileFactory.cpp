/* #include "Factories/ProjectileFactory.hpp"
   #include "Entities/Weapons/Projectile.hpp"

namespace Factories
{

    ProjectileFactory::ProjectileFactory()
    {
    }

    ProjectileFactory::~ProjectileFactory()
    {
    }
    Entity *ProjectileFactory::FactoryMethood(TupleF _position, ID _id)
    {
        ID projec;
        if (_id == empty)
        {
            time_t t;
            srand((unsigned)time(&t));
            unsigned int randomId = (rand() % 3) + 1;
            projec = ID(randomId);
        }
        projec = _id;

        Entity *pE = nullptr;
        switch (projec)
        {
        case ID::PROJECTILE:
            pE = new Entities::Projectile(_position);

        default:
            break;
        }
        if (pE != nullptr)
        {
            pE->initialize();
        }
        return pE;
    }
} // namespace Factories
*/