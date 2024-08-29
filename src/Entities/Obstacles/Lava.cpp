#include "Entities/Obstacles/Lava.hpp"

#define WIDGHT 32.0f
#define HEIGHT 32.0f
#define LAVA_DAMAGE 30

std::string texturepath = "assets/freetileset/png/Tiles/17.png";

namespace Entities
{
    namespace Obstacles
    {
        Lava::Lava(TupleF _position) : Obstacle(_position, Entities::ID::LAVA),
                                       Maxdamage(LAVA_DAMAGE)
        {
        }

        Lava::~Lava()
        {
        }

        void Lava::initialize()
        {
            setSize(WIDGHT, HEIGHT);
            SetTexture(texturepath);
            damage = float(Maxdamage / 2);
            slowness = 1 / (1 + rand() % 3);
        }

        void Lava::update(float dt)
        {
            body->move(0, GRAVITY + forcaBloco);
            if ((int)damage <= Maxdamage)
            {
                damage += dt;
            }
            render();
        }
        void Lava::toObstruct(Entities::Characters::Character *pC)
        {
            pC->reciveDmg((int)damage);
            pC->setSlowness(slowness);
        }

    } // namespace Obstacles

} // namespace Entities
