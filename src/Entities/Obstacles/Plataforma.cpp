#include "Entities/Obstacles/Plataforma.hpp"

#define PATH_PLATAFORMA "assets/freetileset/png/Tiles/2.png"
#define WIDGHT 50.0f
#define HEIGHT 50.0f

namespace Entities
{
    namespace Obstacles
    {
        Plataforma::Plataforma(Coordinates::CoordF _position) : StaticEntity(_position, ID::plataforma)
        {
            initialize();
        }

        Plataforma::~Plataforma()
        {
        }

        void Plataforma::initialize()
        {
            const char *path;
            path = "assets/freetileset/png/Tiles/2.png";
            set_size(Utilis::Coordinates::CoordF(WIDGHT, HEIGHT));
            image.initialize(path, position, size);
        }
    } // namespace Obstacles

} // namespace Entities
