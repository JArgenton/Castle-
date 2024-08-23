#pragma once
#include <time.h>
#include "Entities/Entity.hpp"

using namespace Entities;

namespace Factories
{

    class EntityFactory
    {
    public:
        EntityFactory();
        virtual ~EntityFactory();
        virtual Entity *FactoryMethood(TupleF _position, ID _id) = 0;
    }; // classe geral, sera utilizada para polimorfismo
}
