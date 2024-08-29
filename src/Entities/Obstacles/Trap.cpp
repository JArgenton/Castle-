#include "Entities/Obstacles/Trap.hpp"

#define WIDGHT 32.0f
#define HEIGHT 32.0f
#define TRAP_DAMAGE 30
#define BASE_TRAP_DURATION 3

namespace Entities
{
    namespace Obstacles
    {
        Trap::Trap(TupleF _position) : Obstacle(_position, Entities::ID::TRAP)
        {
        }

        Trap::~Trap()
        {
        }

        void Trap::initialize()
        {

            std::string texturePath("assets/freetileset/png/Object/Bush (4).png");

            setSize(HEIGHT, WIDGHT);
            SetTexture(texturePath);
            float randModifier = 0.5f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.0f)); // valor base * numero entre 0.5 e 1.5
            damage = TRAP_DAMAGE * 1 / randModifier;
            trapDuration = BASE_TRAP_DURATION * randModifier;
            reloadCooldown = trapDuration + 3.0f;
        }
        void Trap::update(float dt)
        {
            reloadTimmer += dt;
            body->move(0, GRAVITY + forcaBloco);
            render();
        }
        void Trap::toObstruct(Characters::Character *pC)
        {
            if (operational())
            {
                body->setFillColor(sf::Color::Red);
                pC->reciveDmg(damage);
                // isTraped ->Character
                pC->isTraped(trapDuration);
                pC->set_velocity(TupleF(0.0f, 0.0f));
                reloadTimmer = 0;
            }
            else
            {
                body->setFillColor(sf::Color::Blue);
            }
        }
        bool Trap::operational()
        {
            return reloadTimmer > reloadCooldown;
        }

    } // namespace Obstacles
} // namespace Entities
