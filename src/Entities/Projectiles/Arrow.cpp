#include "Entities/Projectiles/Arrow.hpp"
#define ARROW_DAMAGE 10
#define ARROW_SPEED 100.0f
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
            set_velocity(TupleF(ARROW_SPEED, 0.0f));
            active = true;
            SetTexture(path);
            body->rotate(90.0f);
        }
        const float Arrow::getDamage()
        {
            return damage;
        }

        void Arrow::update(float dt)
        {
            // Desativa o projétil se o tempo em tela ultrapassar o limite
            if (getPosition().y > 1000)
            {
                active = false;
            }

            // Atualiza a posição do projétil com base na velocidade e delta time
            TupleF velocity = getVelocity();
            velocity.y += GRAVITY;

            body->move(velocity.x * dt, velocity.y * dt);

            render();
        }

        void Arrow::collide(Entity *otherEntity, TupleF intersect)
        {
            active = false;
            moveOnColision(otherEntity, intersect);
        }

    }
}