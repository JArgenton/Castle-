#include "Entities/Obstacles/Plataforma.hpp"

#define PATH_PLATAFORMA "assets/freetileset/png/Tiles/2.png"
#define WIDGHT 50.0f
#define HEIGHT 50.0f

namespace Entities
{
    namespace Obstacles
    {
        Plataforma::Plataforma(TupleF _position) : StaticEntity(_position, ID::plataforma)
        {
            initialize();
        }

        Plataforma::~Plataforma()
        {
        }

        void Plataforma::initialize()
        {
            setSize(WIDGHT, HEIGHT);
            std::string texturepath = "assets/freetileset/png/Tiles/2.png";
            SetTexture(texturepath);
        }
    } // namespace Obstacles

} // namespace Entities
