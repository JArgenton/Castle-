#include "Entities/Obstacles/Armadilha.hpp"

#define WIDGHT 15.0f
#define HEIGHT 15.0f
#define TRAP_DAMAGE 30

namespace Entities
{
    namespace Obstacles
    {
        Armadilha::Armadilha(TupleF _position) : StaticEntity(_position, Entities::ID::ARMADILHA)
        {
        }

        Armadilha::~Armadilha()
        {
        }

        void Armadilha::initialize()
        {
            std::string texturePath("assets/freetileset/png/Object/Bush (4).png");
            setSize(HEIGHT, WIDGHT);
            SetTexture(texturePath);
        }

        unsigned int Armadilha::getDamage() const
        {
            return TRAP_DAMAGE;
        }

        void Armadilha::timeParalized()
        {
        }

    } // namespace Obstacles
} // namespace Entities
