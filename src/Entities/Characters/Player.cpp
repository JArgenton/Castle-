#include "Entities/Characters/Player.hpp"
#include "Entities/Weapons/Weapon.hpp"
#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Obstacles/Armadilha.hpp"
#include "Entities/Projectiles/Arrow.hpp"
#include <math.h>
#define PLAYER_SIZE_X 32.0f
#define PLAYER_SIZE_Y 64.0f
#define PLAYER_VELOCITY 100.0f
#define PLAYER_HEALT 100
#define PLAYER_DMG_COOLDOWN 0.0f
#define JUMP_HEIGH 3.0f
using namespace std;

namespace Entities
{
    using namespace Obstacles;

    namespace Characters
    {
        Player::Player(TupleF _position, Weapons::Weapon *pW, ID _id) : Character(_position, _id),
                                                                        dmgCooldown(PLAYER_DMG_COOLDOWN),
                                                                        canWalk(true),
                                                                        canJump(true),
                                                                        isMoving(false),
                                                                        weapon(pW)

        {
        }
        Player::~Player()
        {
            if (weapon)
            {
                delete weapon;
            }
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
            if (weapon != nullptr && canAtk())
            {
                flagIsAtking = true;
                weapon->atack();
            }
        }

        void Player::incrementPoints(const int points)
        {
            this->points += points;
        }

        void Player::moveOnColision(Entity *other, TupleF intersection)
        {
            TupleF pos = getPosition();
            TupleF otherPos = other->getPosition();

            if (intersection.x > intersection.y)
            {
                if (pos.x < otherPos.x)
                {
                    body->move(intersection.x, 0);
                }
                else
                {
                    body->move(-intersection.x, 0);
                }

                velocity.x = 0.0f;
            }
            else
            {
                if (pos.y < otherPos.y)
                {
                    canJump = true;

                    body->move(0, intersection.y);
                }
                else
                {
                    body->move(0, -intersection.y);
                }
                velocity.y = 0.0f;
            }
        }
        void Player::collide(Entity *other, TupleF intersec)
        {
            if (other != weapon)
                moveOnColision(other, intersec);

            switch (other->getId())
            {
            case ID::PLATAFORMA:
            {
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
            case ID::ARROW:
            {
                reciveDmg(static_cast<Projectiles::Arrow *>(other)->getDamage());
            }
            default:
                break;
            }
        }

        void Player::jump()
        {
            if (canJump)
            {
                velocity.y -= 36 * GRAVITY;
            }
            canJump = false;
        }

        void Player::walk(bool toLeft)
        {
            isMoving = true;
            setFacing(toLeft);
        }

        void Player::stop()
        {
            isMoving = false;
        }

        /*visuals*/
        void Player::initialize()
        {
            active = true;
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
        }

        /*GAME*/
        void Player::updateSprite(const float dt)
        {
            /*TODO*/
        }

        void Player::update(const float dt)
        {
            incrementAtkTimer(dt);
            incrementDmgTimer(dt);

            TupleF position = getPosition();

            if (isMoving)
            {
                velocity.x = PLAYER_VELOCITY;

                if (facingLeft)
                {
                    velocity.x *= -1;
                }
            }
            else
            {
                velocity.x *= 0.5;
            }
            velocity.y += GRAVITY;

            body->move(velocity.x * dt, velocity.y * dt);

            if (weapon)
            {
                weapon->update(dt);
            }
            render(); // desenha player

            dmgTimer += dt;

            if (position.y > 5000)
                active = false;
        }

    }
}