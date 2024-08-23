#include "Entities/Obstacles/Plataforma.hpp"

#define WIDGHT 50.0f
#define HEIGHT 50.0f

namespace Entities
{
    namespace Obstacles
    {
        Plataforma::Plataforma(TupleF _position) : StaticEntity(_position, Entities::ID::PLATAFORMA)
        {
        }

        Plataforma::~Plataforma()
        {
        }

        void Plataforma::initialize()
        {
            setSize(HEIGHT, WIDGHT);
            std::string texturepath = "assets/freetileset/png/Tiles/2.png";
            SetTexture(texturepath);
        }
    } // namespace Obstacles

} // namespace Entities
