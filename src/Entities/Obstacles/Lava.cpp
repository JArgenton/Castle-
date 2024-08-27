#include "Entities/Obstacles/Lava.hpp"

#define WIDGHT 32.0f
#define HEIGHT 32.0f
#define LAVA_DAMAGE 10

std::string texturepath = "assets/freetileset/png/Tiles/17.png";

namespace Entities
{
    namespace Obstacles
    {
        Lava::Lava(TupleF _position) : StaticEntity(_position, Entities::ID::LAVA)
        {
        }

        Lava::~Lava()
        {
        }

        void Lava::initialize()
        {
            setSize(WIDGHT, HEIGHT);
            SetTexture(texturepath);
        }

        unsigned int Lava::getDamage() const
        {
            return LAVA_DAMAGE;
        }

    } // namespace Obstacles

} // namespace Entities
