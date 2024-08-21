#include "Entities/StaticEntity.hpp"

namespace Entities
{
    namespace Obstacles
    {
        class Lava : public StaticEntity
        {
        public:
            Lava(TupleF _position = TupleF(90.0f, 100.0f));
            ~Lava();
            void initialize();
            unsigned int getDamage() const;
        };

    } // namespace Obstacles

} // namespace Entities
