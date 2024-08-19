#include "Entities/Weapons/Sword.hpp"
#include "Entities/Characters/Player.hpp"

#define HIGHT 100.0f
#define WIDITH 20.0f
#define DAMAGE 10
#define ATKCOOLDOWN 5.0f
#define ATKDURATION 3.0f
namespace Entities
{
    namespace Weapons
    {
        Sword::Sword() : Weapon()
        {
        }
        Sword::~Sword()
        {
        }
        void Sword::WeaponInitialize(Characters::Player *pP)
        {
            set_size(Utilis::Coordinates::CoordF(WIDITH, HIGHT));

            setPlayer(pP);
            if (owner)
            {
                ownerPosition = owner->get_position();
                owner->set_atkDamage(DAMAGE);
                owner->set_atkCooldown(ATKCOOLDOWN);
                owner->set_atkDuration(ATKDURATION);
                setPosition();
            }
            else
            {
                std::cout << "erro em SWORD, owner nulo " << std::endl;
            }
            const char *texturepath = "assets/sword.png";
            image.initialize(texturepath, position, size);
        }
        void Sword::atack()
        {
            /*TODO:
            Modificar o tam de weapon para o range de ataque
            retornar para o valor padrao dps do final do ataque
            fazer na update*/
        }
        void Sword::setPosition()
        {
            if (owner)
            {
                position = Coordinates::CoordF(ownerPosition.x + owner->get_size().x + 10.0f, ownerPosition.y + owner->get_size().y + 10.0f);
            }
        }
        void Sword::update(const float dt)
        {
            setPosition();
            image.update(position);
            render();
        }
        void Sword::render()
        {
            image.render();
        }
    }

} // namespace Entities
