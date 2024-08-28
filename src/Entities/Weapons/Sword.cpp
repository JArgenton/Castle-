#include "Entities/Weapons/Sword.hpp"
#include "Entities/Characters/Player.hpp"

#define HIGHT 32.0f
#define WIDITH 16.0f
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
            setSize(WIDITH, HIGHT);

            setPlayer(pP);
            if (owner)
            {
                owner->set_atkDamage(DAMAGE);
                owner->set_atkCooldown(ATKCOOLDOWN);
                owner->set_atkDuration(ATKDURATION);
                setPosition(owner->getPosition());
            }
            else
            {
                std::cout << "erro em SWORD, owner nulo " << std::endl;
            }
            std::string texturepath = "assets/sword.png";
            SetTexture(texturepath);
        }
        void Sword::atack()
        {
            /*TODO:
            Modificar o tam de weapon para o range de ataque
            retornar para o valor padrao dps do final do ataque
            fazer na update*/
        }
        void Sword::update(const float dt)
        {
            if (owner)
            {
                TupleF position;
                position = owner->getPosition();
                if (!owner->isFacingLeft())
                {
                    position.x = position.x + owner->getSize().x / 2 + 5.0f;
                }
                else
                {
                    position.x = position.x - owner->getSize().x / 2 - 5.0f;
                }
                setPosition(position);
            }
            render();
        }
        void Sword::updateSprite(const float dt)
        {
            /*TODO */
        }

    }

} // namespace Entities
