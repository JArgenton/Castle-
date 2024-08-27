#include "Factories/ObstaclesFactory.hpp"
#include "Entities/Obstacles/Armadilha.hpp"
#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Obstacles/Plataforma.hpp"

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
                obstacle = ID::ARMADILHA;
            }
            else if (randomId == 1)
            {
                obstacle = ID::ARMADILHA;
            }
            else
            {
                obstacle = ID::PLATAFORMA;
            }
        }
        else
        {
            obstacle = _id;
        }

        Entity *pE = nullptr;
        switch (obstacle)
        {
        case ARMADILHA:
            pE = new Entities::Obstacles::Armadilha(_position);

            break;
        case LAVA:
            pE = new Entities::Obstacles::Lava(_position);

            break;
        case PLATAFORMA:
            pE = new Entities::Obstacles::Plataforma(_position);
            break;

        default:
            break;
        }
        pE->initialize();
        return pE;
    }

} // namespace Factories
