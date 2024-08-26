#include "Entities/Projectiles/Arrow.hpp"
#define ARROW_DAMAGE 10
#define ARROW_SPEED 1.0f
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
            setSize(HEIGHT, LENTH);
            setDamage(ARROW_DAMAGE);
            set_velocity(TupleF(ARROW_SPEED, 0.0f));
            SetTexture(path);
        }
        const float Arrow::getDamage()
        {
            return damage;
        }

        void Arrow::update(float dt)
        {

            // Desativa o projétil se o tempo em tela ultrapassar o limite
            if (getPosition().y > 1000)
                active = false;

            // Atualiza a posição do projétil com base na velocidade e delta time
            TupleF velocity = getVelocity();
            TupleF newPosition = getPosition();
            velocity.y += GRAVITY;

            newPosition.x += velocity.x * dt;
            newPosition.y += velocity.y * dt;

            setPosition(newPosition);

            // Atualiza a posição do RectangleShape do projétil
            setPosition(newPosition);
            render();

            if (!active)
            {
                delete this;
            }
        }

        void Arrow::collide(Entity *otherEntity, TupleF intersect)
        {
            active = false;
            moveOnColision(otherEntity, intersect);
        }

    }
}