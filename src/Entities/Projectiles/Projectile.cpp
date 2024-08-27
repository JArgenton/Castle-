#include "Entities/Projectiles/Projectile.hpp"

namespace Entities
{
    namespace Projectiles
    {
        Projectile::Projectile(TupleF _position, ID _id) : MovingEntity(_position, _id),
                                                           damage(0)
        {
        }

        Projectile::~Projectile()
        {
        }
        void Projectile::setDamage(const int _damage)
        {
            damage = _damage;
        }

        const int Projectile::getDamage()
        {
            return damage;
        }

        void Projectile::update(float dt)
        {

            // Desativa o projétil se o tempo em tela ultrapassar o limite
            if (getPosition().y > 1000)
                active = false;

            // Atualiza a posição do projétil com base na velocidade e delta time
            TupleF velocity = getVelocity();
            TupleF newPosition = getPosition();
            velocity.y += GRAVITY;
            newPosition.x += velocity.x * dt;
            newPosition.y += velocity.y * dt * 3;
            setPosition(newPosition);

            // Atualiza a posição do RectangleShape do projétil
            setPosition(newPosition);

            // Remove a renderização se o projétil estiver inativo
            if (active)
            {
                render();
            }
        }

        void Projectile::collide(Entity *otherEntity, TupleF intersect)
        {
            active = false;
            moveOnColision(otherEntity, intersect);
        }

    }
}