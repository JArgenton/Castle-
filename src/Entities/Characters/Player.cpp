#include "Entities/Characters/Player.hpp"
#include "Entities/Weapons/Weapon.hpp"
#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Obstacles/Armadilha.hpp"
#include "Entities/Weapons/Projectile.hpp"

#define PLAYER_SIZE_X 100.0f
#define PLAYER_SIZE_Y 100.0f
#define PLAYER_VELOCITY 0.8f
#define PLAYER_HEALT 100
#define PLAYER_DMG_COOLDOWN 0.0f
#define JUMP_HEIGH 3.0f
using namespace std;

namespace Entities
{
    using namespace Obstacles;

    namespace Characters
    {
        Player::Player(Weapons::Weapon *pW, ID _id) : Character(TupleF(100.0f, 100.0f), _id),
                                                      dmgCooldown(PLAYER_DMG_COOLDOWN),
                                                      canWalk(true),
                                                      canReciveDmg(true),
                                                      canJump(true),
                                                      isMoving(true),
                                                      dmgTimer(0),
                                                      weapon(pW)

        {
        }
        Player::~Player()
        {
            delete weapon;
            weapon = nullptr;
        }

        /*SETs*/
        void Player::set_weapon(Weapons::Weapon *pweapon)
        {
            if (weapon == nullptr)
            {
                weapon = pweapon;
                weapon->WeaponInitialize(this);
            }
        }

        void Player::setJump(bool jump)
        {
            canJump = jump;
        }

        void Player::setWalk(bool walk)
        {
            canWalk = walk;
        }

        /*GETs*/
        Weapons::Weapon *Player::get_weapon()
        {
            return weapon;
        }

        const int Player::getPoints() const
        {
            return points;
        }

        /*actions*/
        void Player::atack()
        {
            if (weapon != nullptr)
            {
                weapon->atack();
            }
        }

        void Player::reciveDmg(int dmg)
        {
            if (canReciveDmg)
            {
                health -= dmg;
                if (health <= 0)
                {
                    active = false;
                }
                dmgTimer = 0;
            }
        }

        void Player::incrementPoints(const int points)
        {
            this->points += points;
        }

        void Player::collide(Entity *other, TupleF intersec)
        {
            moveOnColision(other, intersec);

            switch (other->getId())
            {
            case ID::PLATAFORMA:
            {
                canJump = true;
                break;
            }

            case ID::ARMADILHA:
            {
                /*TODO*/
                break;
            }
            case ID::LAVA:
            {
                Lava *lava = dynamic_cast<Lava *>(other);
                if (lava)
                {
                    reciveDmg(lava->getDamage());
                }
                break;
            }
            case ID::PROJECTILE:
            {
                Projectile *proj = dynamic_cast<Projectile *>(other);
                if (proj)
                {
                    reciveDmg(proj->getDamage());
                }
                printf("colidiu flecha");
                break;
            }
            default:
                break;
            }
        }

        void Player::jump()
        {
            if (canJump)
            {
                velocity.y = GRAVITY * 3;
            }
        }
        void Player::walk(bool toLeft)
        {
            isMoving = true;
            facingLeft = toLeft;
        }
        void Player::stop()
        {
            isMoving = false;
        }

        /*visuals*/
        void Player::initialize()
        {
            setSize(PLAYER_SIZE_X, PLAYER_SIZE_Y); // chama a set Origin
            std::string texturepath = "assets/player.png";
            SetTexture(texturepath);

            if (weapon)
            {
                weapon->WeaponInitialize(this); // todo
            }
        }
        void Player::execute()
        {
            /*TODO*/
        }

        /*GAME*/
        void Player::updateSprite(const float dt)
        {
            /*TODO*/
        }

        void Player::update(const float dt)
        {
            incrementAtkTimer(dt);
            TupleF position = getPosition();

            if (isMoving)
            {
                velocity.x = PLAYER_VELOCITY;

                if (facingLeft)
                    velocity.x *= -1;
            }
            else
                velocity.x *= 0.05;
            velocity.y += GRAVITY;

            position.x += velocity.x * dt;
            position.y += velocity.y * dt;

            setPosition(position); // atualiza a posiçao da imagem

            if (weapon)
            {
                weapon->update(dt);
            }
            render(); // desenha player

            dmgTimer += dt;

            if (position.y > 1000)
                active = false;
        }

    }
}