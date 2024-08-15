#include "Entities/Weapons/Weapon.hpp"

namespace Entities
{
    namespace Characters
    {
        class Player; // Declaração de classe avançada
    }
    namespace Weapons
    {

        class Sword : public Weapon
        {
        private:
            /* data */
        public:
            Sword(/* args */);
            ~Sword();
            void WeaponInitialize(Characters::Player *pP);
        };

    }
}