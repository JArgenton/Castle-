#include "Entities/Characters/Player.hpp"
#include "Entities/Weapons/Sword.hpp"

#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Obstacles/Trap.hpp"
#include "Entities/Obstacles/Plataform.hpp"

#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Characters/Enemies/Soldier.hpp"
#include "Entities/Characters/Enemies/BigBoss.hpp"

#include "Entities/Projectiles/Arrow.hpp"
#include "Entities/Projectiles/Hook.hpp"
#include <math.h>
#define PLAYER_SIZE_X 32.0f
#define PLAYER_SIZE_Y 64.0f
#define PLAYER_VELOCITY 100.0f
#define PLAYER_HEALTH 1000
#define PLAYER_DMG_COOLDOWN 0.0f
#define JUMP_HEIGH 3.0f
using namespace std;

namespace Entities
{
    using namespace Obstacles;

    namespace Characters
    {
        bool Player::PlayerCreationFlag(true);
        Player::Player(TupleF _position, Weapons::Weapon *pW, ID _id) : Character(_position, _id),
                                                                        fullyCreated(false),

                                                                        dmgCooldown(PLAYER_DMG_COOLDOWN),
                                                                        canWalk(true),
                                                                        canJump(true),
                                                                        isMoving(false),
                                                                        weapon(pW)

        {
        }
        Player::~Player()
        {
            weapon->setInactive();
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

        void Player::setPoints(int points)
        {
            points = points;
        }

        /*GETs*/
        Weapons::Weapon *Player::get_weapon()
        {
            return weapon;
        }

        int Player::getPoints()
        {
            return points;
        }

        const int Player::getTotalHealth() const
        {
            return PLAYER_HEALTH;
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
            switch (other->getId())
            {
            case ID::PLATAFORM:
            {
                moveOnColision(other, intersec);
                static_cast<Plataform *>(other)->toObstruct(this);
                break;
            }
            case ID::LAVA:
            {
                moveOnColision(other, intersec);
                static_cast<Lava *>(other)->toObstruct(this);
                break;
            }
            case ID::TRAP:
            {
                moveOnColision(other, intersec);
                static_cast<Trap *>(other)->toObstruct(this);
                break;
            }
            case ID::ARROW:
            {
                reciveDmg(static_cast<Projectiles::Arrow *>(other)->getDamage());
                break;
            }
            case ID::WEAPON:
            {
                if (other != weapon)
                {
                    Player *owner = dynamic_cast<Weapons::Sword *>(other)->getOwner();
                    if (owner->isAtking())
                    {
                        reciveDmg(owner->getAtkDamage());
                    }
                }

                break;
            }
            case ID::ARCHER:
            {
                moveOnColision(other, intersec);

                static_cast<Enemies::Archer *>(other)->toDamage(this);
                break;
            }
            case ID::SOLDIER:
            {
                moveOnColision(other, intersec);

                static_cast<Enemies::Archer *>(other)->toDamage(this);
                break;
            }
            case ID::HOOK:
            {
                moveOnColision(other, intersec);

                static_cast<Projectiles::Hook *>(other)->hook(this);
                break;
            }
            case ID::BOSS:
            {
                moveOnColision(other, intersec);

                static_cast<Enemies::BigBoss *>(other)->toDamage(this);
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
                velocity.y -= 38 * GRAVITY;
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

        bool Player::getFullyCreated()
        {
            return fullyCreated;
        }

        /*visuals*/
        void Player::initialize()
        {
            if (PlayerCreationFlag)
            {
                points = 0;
                set_health(PLAYER_HEALTH);
                active = true;
                setSize(PLAYER_SIZE_X, PLAYER_SIZE_Y); // chama a set Origin
                std::string texturepath = "assets/player.png";
                SetTexture(texturepath);

                if (weapon)
                {
                    weapon->WeaponInitialize(this); // todo
                }
                PlayerCreationFlag = false;
                fullyCreated = true;
            }
            else
            {
                points = 0;
                active = true;
                set_health(200);
                setSize(0.1f, 0.1f); // chama a set Origin

                if (weapon)
                {
                    weapon->setSize(0.1f, 0.1f);
                }
                PlayerCreationFlag = true;
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
            if (!isActive())
            {
                setPosition(TupleF(9000.0f, 9000.0f));
                return;
            }
            trapTimmer += dt;
            incrementAtkTimer(dt);
            incrementDmgTimer(dt);

            TupleF position = getPosition();
            if (canMove())
            {
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