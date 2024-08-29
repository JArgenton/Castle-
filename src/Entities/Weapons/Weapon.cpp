#include "Entities/Weapons/Weapon.hpp"
#include "Entities/Characters/Player.hpp"

namespace Entities
{
    namespace Weapons
    {
        Weapon::Weapon() : MovingEntity(TupleF(0.0f, 0.0f), WEAPON),
                           owner(nullptr)
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
        Characters::Player *Weapon::getOwner()
        {
            return owner;
        }
        ID
        Weapon::getOwnerID()
        {
            if (owner)
            {
                return owner->getId();
            }
            else
            {
                cout << "desespero" << endl;
            }
        }
        void Weapon::setInactive()
        {
            active = false;
        }

    }

}