#include "Factories/ObstaclesFactory.hpp"
#include "Entities/Obstacles/Trap.hpp"
#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Obstacles/Plataform.hpp"

namespace Factories
{
    ObstaclesFactory::ObstaclesFactory(/* args */)
    {
    }

    ObstaclesFactory::~ObstaclesFactory()
    {
    }
    Entity *ObstaclesFactory::FactoryMethood(TupleF _position, ID _id)
    {
        ID obstacle;
        if (_id == empty)
        {

            int randomId = rand() % 3;

            if (randomId == 0)
            {
                obstacle = ID::TRAP;
            }
            else if (randomId == 1)
            {
                obstacle = ID::LAVA;
            }
            else
            {
                obstacle = ID::PLATAFORM;
            }
        }
        else
        {
            obstacle = _id;
        }

        Entity *pE = nullptr;
        switch (obstacle)
        {
        case TRAP:
            pE = new Entities::Obstacles::Trap(_position);

            break;
        case LAVA:
            pE = new Entities::Obstacles::Lava(_position);

            break;
        case PLATAFORM:
            pE = new Entities::Obstacles::Plataform(_position);
            break;

        default:
            break;
        }
        pE->initialize();
        return pE;
    }

} // namespace Factories
