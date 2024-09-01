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
#define PLAYER_HEALTH 2500
#define PLAYER_DMG_COOLDOWN 0.0f
#define JUMP_HEIGH 3.0f
using namespace std;

#define ATACK_PATH "assets/Knight_2/Attack 2.png"
#define WALK_PATH "assets/Knight_2/Run.png"
#define IDLE "assets/Knight_2/Idle.png"
#define DAMAGE "assets/Knight_2/Hurt.png"
#define JUMP "assets/Knight_2/Jump.png"
#include "GraphElements/MultiFrameAnimation.hpp"
using namespace GraphicalElements;

namespace Entities
{
    using namespace Obstacles;

    namespace Characters
    {
        bool Player::PlayerCreationFlag(true);
        Player::Player(TupleF _position, Weapons::Weapon *pW, ID _id) : Character(_position, _id),
                                                                        fullyCreated(false),
                                                                        pointsGranted(false),
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

        void Player::disablePlayerCreationFlag()
        {
            PlayerCreationFlag = false;
        }

        void Player::setFullyCreated(bool fullyCreated)
        {
            this->fullyCreated = fullyCreated;
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
                pointsGranted = false;
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
            case ID::PLATAFORM1:
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
                if (isAtking() && !pointsGranted) // Verifica se já concedeu pontos
                {
                    incrementPoints(10);
                    pointsGranted = true; // Marca como concedido
                }
            }
            case ID::SOLDIER:
            {
                moveOnColision(other, intersec);

                static_cast<Enemies::Soldier *>(other)->toDamage(this);

                if (isAtking() && !pointsGranted) // Verifica se já concedeu pontos
                {
                    incrementPoints(20);
                    pointsGranted = true; // Marca como concedido
                }
            }
            case ID::HOOK:
            {
                moveOnColision(other, intersec);

                static_cast<Projectiles::Hook *>(other)->hook(this);
                break;
            }
            case ID::ARROW:
            {
                moveOnColision(other, intersec);

                reciveDmg(static_cast<Projectiles::Arrow *>(other)->getDamage());
                break;
            }
            case ID::BOSS:
            {
                moveOnColision(other, intersec);

                static_cast<Enemies::BigBoss *>(other)->toDamage(this);

                if (isAtking() && !pointsGranted) // Verifica se já concedeu pontos
                {
                    cout << "points granted" << endl;
                    incrementPoints(40);
                    pointsGranted = true; // Marca como concedido
                }
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

                velocity.y = 38 * -GRAVITY;
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
                set_health(PLAYER_HEALTH);
                setSize(0.1f, 0.1f); // chama a set Origin

                if (weapon)
                {
                    weapon->setSize(0.1f, 0.1f);
                }
                PlayerCreationFlag = true;
            }
            sprite.addNewAnimation(AnimationID::walk, WALK_PATH, 7, 0.1);
            sprite.addNewAnimation(AnimationID::attack, ATACK_PATH, 4, 0.3);
            sprite.addNewAnimation(AnimationID::idle, IDLE, 4, 10);
            sprite.addNewAnimation(AnimationID::jump, JUMP, 6, 0.3);
            sprite.addNewAnimation(AnimationID::reciveDamage, DAMAGE, 2, 2);
        }

        void Player::initializeAfterLoad()
        {

            if (PlayerCreationFlag)
            {
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
                active = true;
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
            TupleF pos = getPosition();
            pos(pos.x, pos.y - 10);
            if (!canReciveDmg())
            {

                sprite.update(AnimationID::reciveDamage, facingLeft, pos, dt);
            }
            else if (isAtking())
            {
                sprite.update(AnimationID::attack, facingLeft, pos, dt);
            }
            else if (!canMove() || !isMoving)
            {
                sprite.update(AnimationID::idle, facingLeft, pos, dt);
            }
            else if (!canJump)
            {
                sprite.update(AnimationID::jump, facingLeft, pos, dt);
            }
            else if (isMoving)
            {
                sprite.update(AnimationID::walk, facingLeft, pos, dt);
            }
        }

        void Player::update(const float dt)
        {
            if (!isActive() || !getFullyCreated())
            {
                setPosition(TupleF(9000.0f, 9000.0f));
                return;
            }
            trapTimmer += dt;
            dmgTimer += dt;

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
            updateSprite(dt);
            render(); // desenha player

            if (position.y > 5000)
                active = false;
        }

    }
}