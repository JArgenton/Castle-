#include "Entities/Weapons/Weapon.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities
{
    namespace Weapons
    {
        Weapon::Weapon() : MovingEntity(Coordinates::CoordF(0.0f, 0.0f), WEAPON),
                           owner(nullptr),
                           ownerPosition(position)

        {
        }
        Weapon::~Weapon()
        {
            owner = nullptr;
        }
        void Weapon::setPlayer(Characters::Player *pP)
        {
            owner = pP;
        }
    }

}