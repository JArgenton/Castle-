#include "Entities/Obstacles/Armadilha.hpp"

#define WIDGHT 80.0f
#define HEIGHT 80.0f
#define LAVA_DAMAGE 10

namespace Entities
{
    namespace Obstacles
    {
        std::string Armadilha::texturepath("assets/freetileset/png/Tiles/17.png");

        Armadilha::Armadilha(TupleF _position) : StaticEntity(_position, Entities::ID::LAVA)
        {
        }

        Armadilha::~Armadilha()
        {
        }

        void Armadilha::initialize()
        {
            setSize(WIDGHT, HEIGHT);
            SetTexture(texturepath);
        }

        unsigned int Armadilha::getDamage() const
        {
            return LAVA_DAMAGE;
        }

    } // namespace Obstacles

} // namespace Entities
