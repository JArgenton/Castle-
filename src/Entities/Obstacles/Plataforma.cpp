#include "Entities/Obstacles/Plataforma.hpp"

#define WIDGHT 32.0f
#define HEIGHT 32.0f

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
            setSize(WIDGHT, HEIGHT);
            std::string texturepath = "assets/freetileset/png/Tiles/2.png";
            // SetTexture(texturepath);
            body->setFillColor(sf::Color::Blue);
        }
    } // namespace Obstacles

} // namespace Entities
