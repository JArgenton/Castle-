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
            Sword();
            ~Sword();
            void atack();
            void WeaponInitialize(Characters::Player *pP);
            void updateSprite(const float dt);
            void update(const float dt);
        };

    }
}
