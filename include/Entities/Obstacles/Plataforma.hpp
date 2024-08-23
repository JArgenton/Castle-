#pragma once
#include "Entities/StaticEntity.hpp"

namespace Entities
{
    namespace Obstacles
    {
        class Plataforma : public StaticEntity
        {
        public:
            Plataforma(TupleF _position = TupleF(80.0f, 100.0f));
            ~Plataforma();
            void initialize();
        };

    } // namespace Obstacles

}