
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

    }
}