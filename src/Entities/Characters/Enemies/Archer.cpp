#include "Entities/Characters/Enemies/Archer.hpp"
#include "States/Level.hpp"
#include "Math/geometry.hpp"
#define ARCHER_DMG 10
#define ATK_DURATION 1.0f
#define ARCHER_ATK_COOLDOWN 1.0f
#define ARCHER_HEALTH 150
#define ARCHER_WIDGHT 32.0f
#define ARCHER_HEIGHT 64.0f

#define ATACK_PATH "assets/Skeleton_Archer/Shot_1.png"
#define WALK_PATH "assets/Skeleton_Archer/Evasion.png"
#define IDLE "assets/Skeleton_Archer/Idle.png"

std::string ARCHER_PATH = "assets/arqueiro.jpeg";

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            Archer::Archer(TupleF position) : Enemy(position, ARCHER)

            {
            }

            Archer::~Archer()
            {
                pPlayer1 = nullptr;
                pPlayer2 = nullptr;
            }

            void Archer::shoot()
            {
                TupleF archerPosition = getPosition();
                TupleF archerSize = getSize();
                TupleF pPos = getPlayerPosition();
                pPos.y -= 40;
                TupleF projectilePosition;

                if (facingLeft)
                {
                    projectilePosition = TupleF(archerPosition.x - archerSize.x, archerPosition.y - archerSize.y / 2);
                }
                else
                {
                    projectilePosition = TupleF(archerPosition.x + archerSize.x, archerPosition.y - archerSize.y / 2);
                }

                TupleF direction = geometry::getDirectionalVector(projectilePosition, pPos);

                States::Level::createProjectile(projectilePosition, ID::ARROW, direction);
            }

            void Archer::update(const float dt)
            {
                execute();

                Character::incrementAtkTimer(dt);
                incrementDmgTimer(dt);

                velocity.y += GRAVITY;
                body->move(velocity.x * dt, velocity.y * dt);

                updateSprite(dt);
                render();
            }
            void Archer::atack()
            {
                if (canAtk())
                {
                    flagIsAtking = true;
                    shoot();
                }
            }

            void Archer::initialize()
            {

                set_health(ARCHER_HEALTH);
                set_atkCooldown(ARCHER_ATK_COOLDOWN);
                set_atkDuration(ATK_DURATION);
                atkTimer = 0.0;
                coolDownTimer = 0.0f;

                set_atkDamage(ARCHER_DMG);
                setSize(ARCHER_WIDGHT, ARCHER_HEIGHT);

                sprite.addNewAnimation(AnimationID::attack, ATACK_PATH, 15, 0.3);
                sprite.addNewAnimation(AnimationID::walk, WALK_PATH, 6, 0.5);
                sprite.addNewAnimation(AnimationID::idle, WALK_PATH, 7, 1);
            }

            void Archer::execute()
            {
                if (getPlayerPosition().x < getPosition().x)
                {
                    setFacing(true);
                }
                else
                {
                    setFacing(false);
                }

                if (updatePlayerDistance() < 480.0f)
                {
                    atack();
                }
            }

            void Archer::updateSprite(const float dt)
            {
                TupleF pos = getPosition();
                pos(pos.x, pos.y - getSize().y / 2);
                if (isAtking())
                {

                    sprite.update(AnimationID::attack, facingLeft, pos, dt);
                }
                else if (velocity.x != 0)
                {
                    sprite.update(AnimationID::walk, facingLeft, pos, dt);
                }
                else
                {
                    sprite.update(AnimationID::idle, facingLeft, pos, dt);
                }
            }

            void Archer::toDamage(Player *pP)
            {
                pP->isTraped(1.0f);
                if (facingLeft)
                    pP->set_velocity(TupleF(-150.0f, -150.0f));
                else
                {
                    pP->set_velocity(TupleF(150.0f, -150.0f));
                }
            }

        }

    }
}
