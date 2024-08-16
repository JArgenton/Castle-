#include "Entities/Characters/Player.hpp"
#include "Entities/Weapons/Weapon.hpp"
#define PLAYER_SIZE_X 100.0f
#define PLAYER_SIZE_Y 100.0f
#define PLAYER_VELOCITY 0.1f
#define PLAYER_HEALT 100
#define PLAYER_DMG_COOLDOWN 0.0f
#define JUMP_HEIGH 3.0f

namespace Entities
{
    namespace Characters
    {
        Player::Player(Weapons::Weapon *pW) : Character(Coordinates::CoordF(100.0f, 100.0f), PLAYER),
                                              dmgCooldown(PLAYER_DMG_COOLDOWN),
                                              canWalk(true),
                                              canReciveDmg(true),
                                              canJump(true),
                                              isMoving(true),
                                              dmgTimer(0),
                                              weapon(pW)

        {
            initialize();
        }
        Player::~Player()
        {
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
            else
            {
                weapon = pweapon;
            }
        }

        /*GETs*/
        Weapons::Weapon *Player::get_weapon()
        {
            return weapon;
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
        void Player::colide(Entity *other, Coordinates::CoordF intersec)
        {
            /*TODO*/
        }
        void moveOnColision(Entity *other)
        {
            /*todo*/
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
            set_size(Coordinates::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y));
            if (weapon)
            {
                weapon->WeaponInitialize(this); // todo
            }
            const char *texturepath = "assets/player.png";
            image.initialize(texturepath, position, size);
        }
        void Player::render()
        {
            image.render();
        }

        /*Colisions*/
        void Player::moveOnColision(Entity *other)
        {
            /*TODO*/
        }

        /*GAME*/
        void Player::update(const float dt)
        {
            incrementAtkTimer(dt);

            if (isMoving)
            {
                velocity.x = PLAYER_VELOCITY;

                if (facingLeft)
                    velocity.x *= -1;
            }
            else
                velocity.x *= 0.05;
            velocity.y += 0;

            position.x += velocity.x * dt;
            position.y += velocity.y * dt;

            image.update(position);
            if (weapon)
            {
                weapon->update(dt);
            }
            render();

            dmgTimer += dt;

            if (position.y > 1000)
                active = false;
        }

    }
}