#include "Entities/Weapons/Sword.hpp"
#include "Entities/Characters/Player.hpp"

#define HIGHT 48.0f
#define WIDITH 32.0f
#define DAMAGE 50
#define ATKCOOLDOWN 0.5f
#define ATKDURATION 1.0f
namespace Entities
{
    namespace Weapons
    {
        Sword::Sword() : Weapon(),
                         critChance(rand() % 10),
                         crit(float((rand() % 10) / 10 + 1.5f))
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
            std::string texturepath = "assets/espada2.png";
            SetTexture(texturepath);
        }
        void Sword::atack()
        {
            if (rand() % 10 >= critChance)
            {
                owner->set_atkDamage(static_cast<int>(DAMAGE * crit));
            }
            else
            {
                owner->set_atkDamage(static_cast<int>(DAMAGE));
            }
        }
        void Sword::update(const float dt)
        {
            if (owner)
            {
                TupleF position;
                position = owner->getPosition();
                if (!owner->isFacingLeft())
                {
                    position(position.x + owner->getSize().x / 2 + 5.0f, position.y - 10.0f);
                }
                else
                {

                    position(position.x - owner->getSize().x / 2 - 5.0f, position.y - 10.0f);
                }
                if (owner->isAtking())
                {

                    if (!owner->isFacingLeft())
                    {

                        body->setRotation(90);
                        position.x += 15;
                    }

                    else
                    {
                        body->setScale(-1, 1);

                        body->setRotation(-90);
                        position.x -= 15;
                    }
                }
                else
                {
                    body->setScale(1, 1);

                    body->setRotation(35);
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
