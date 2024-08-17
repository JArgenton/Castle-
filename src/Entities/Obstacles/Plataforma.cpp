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

        void Plataforma::update(float dt)
        {
            image.update(position);
        }

        void Plataforma::initialize()
        {
            set_size(Utilis::Coordinates::CoordF(WIDGHT, HEIGHT));
            image.initialize(PATH_PLATAFORMA, position, size);
        }

        void Plataforma::colide(Entity *other, Coordinates::CoordF intersec)
        {
        }

    } // namespace Obstacles

} // namespace Entities
