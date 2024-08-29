
#include "Entities/Projectiles/Arrow.hpp"
#include "Entities/Weapons/Sword.hpp"
#include "Entities/Characters/Player.hpp"
#include "Utilis/geometry.hpp"
#define ARROW_DAMAGE 10
#define ARROW_SPEED 500.0f
#define HEIGHT 10.0F
#define LENTH 30.0F

namespace Entities
{
    namespace Projectiles
    {
        std::string path = "assets/freetileset/png/Object/Mushroom_1.png";

        Arrow::Arrow(TupleF _position) : Projectile(_position, ARROW)
        {
        }

        Arrow::~Arrow()
        {
        }
        void Arrow::initialize()
        {
            setSize(10.0f, 30.0f);
            setDamage(ARROW_DAMAGE);
            damage = 10;
            active = true;
            SetTexture(path);
            body->rotate(90.0f);
            velocity(0.0f, 0.0f);
        }
        const float Arrow::getDamage()
        {
            return damage;
        }
        void Arrow::setDirection(TupleF _direction)
        {
            velocity = _direction;

            geometry::escalateVector(&velocity, ARROW_SPEED);
        }
        void Arrow::update(float dt)
        {
            // Desativa o projétil se o tempo em tela ultrapassar o limite
            if (getPosition().y > 10000)
            {
                active = false;
            }

            // Atualiza a posição do projétil com base na velocidade e delta time
            velocity.y += GRAVITY * 0.4f;
            body->move(velocity.x * dt, velocity.y * dt);

            render();
        }

        void Arrow::collide(Entity *otherEntity, TupleF intersect)
        {
            active = false;
            moveOnColision(otherEntity, intersect);
            ID otherID = otherEntity->getId();
            if (otherID == WEAPON)
            {
                Characters::Player *pP = dynamic_cast<Weapons::Sword *>(otherEntity)->getOwner();
                if (!pP->isAtking())
                {
                    pP->reciveDmg(damage);
                }
            }
        }

    }
}