#include "Entities/Characters/Player.hpp"

#define WPON_X_POS 110.0f
#define WPON_Y_POS 110.0f

namespace Entities
{
    namespace Weapons
    {
        Weapon::Weapon() : MovingEntity(Coordinates::CoordF(WPON_X_POS, WPON_Y_POS), WEAPON),
                           pPlayer(nullptr),
                           type(empty)

        {
            AtkCooldown = 0;
            AtkDuration = 0;
            AtkRange = 0;
            AtkDamage = 0;
        }
        Weapon::~Weapon()
        {
            pPlayer = nullptr;
        }
    }

}