#include "Entities/Obstacles/Plataform.hpp"

#define WIDGHT 32.0f
#define HEIGHT 32.0f
#define FAKE_PLAT_DAMAGE 10
namespace Entities
{
    namespace Obstacles
    {
        Plataform::Plataform(TupleF _position) : Obstacle(_position, Entities::ID::PLATAFORM),
                                                 fake(rand() % 100 == 1 ? true : false)
        {
        }

        Plataform::~Plataform()
        {
        }

        void Plataform::initialize()
        {
            setSize(WIDGHT, HEIGHT);
            std::string texturepath = "assets/freetileset/png/Tiles/2.png";
            SetTexture(texturepath);
        }
        void Plataform::update(float dt)
        {
            body->move(0, GRAVITY + forcaBloco);
            render();
        }
        void Plataform::toObstruct(Entities::Characters::Character *pC)
        {
            if (fake)
            {
                pC->reciveDmg(FAKE_PLAT_DAMAGE);
            }
        }
    } // namespace Obstacles

} // namespace Entities
