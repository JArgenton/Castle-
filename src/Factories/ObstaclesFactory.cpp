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

            if (rand() % 2)
            {
                obstacle = ID::LAVA;
            }
            else
            {
                obstacle = ID::PLATAFORM1;
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
        case PLATAFORM1:
            pE = new Entities::Obstacles::Plataform(_position);

            break;
        default:

            break;
        }
        pE->initialize();

        return pE;
    }

} // namespace Factories
