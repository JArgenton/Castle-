#include "Factories/EnemiesFactory.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Characters/Enemies/Soldier.hpp"
#include "Entities/Characters/Enemies/Dumb.hpp"

namespace Factories
{
    EnemiesFactory::EnemiesFactory()
    {
    }

    EnemiesFactory::~EnemiesFactory()
    {
    }
    Entity *EnemiesFactory::FactoryMethood(TupleF _position, ID _id)
    {
        ID enemy;
        if (_id == empty)
        {
            time_t t;
            srand((unsigned)time(&t));
            unsigned int randomId = (rand() % 3) + 1;
            enemy = ID(randomId);
        }
        enemy = _id;

        Entity *pE = nullptr;
        switch (enemy)
        {
        case SOLDIER:
            pE = new Entities::Characters::Enemies::Soldier(_position);

            break;
        case ARCHER:
            pE = new Entities::Characters::Enemies::Archer(_position);

            break;
        case DUMB:
            pE = new Entities::Characters::Enemies::Dumb(_position);
            break;

        default:
            break;
        }
        pE->initialize();
        return pE;
    }
} // namespace Factories
