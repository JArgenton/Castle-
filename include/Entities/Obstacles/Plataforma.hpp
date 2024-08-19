#include "Entities/StaticEntity.hpp"

namespace Entities
{
    namespace Obstacles
    {
        class Plataforma : public StaticEntity
        {
        public:
            Plataforma(Coordinates::CoordF _position = Coordinates::CoordF(80.0f, 100.0f));
            ~Plataforma();
            void initialize();
        };

    } // namespace Obstacles

}