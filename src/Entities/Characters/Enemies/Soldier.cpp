#include "Entities/Characters/Enemies/Soldier.hpp"
#include "Entities/Characters/Player.hpp"
#include "GraphElements/MultiFrameAnimation.hpp"

#include <math.h>

#define BASE_SPEED 55.0f

#define ATACK_PATH "assets/Skeleton_Warrior/Run+attack.png"
#define WALK_PATH "assets/Skeleton_Warrior/Walk.png"
#define IDLE "assets/Skeleton_Warrior/Idle.png"
#define HURT "assets/Skeleton_Warrior/Hurt.png"
using namespace GraphicalElements;
namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {

            Soldier::Soldier(TupleF _position) : Enemy(_position, ID::SOLDIER)
            {
            }
            Soldier::~Soldier()
            {
            }

            void Soldier::initialize()
            {

                set_health(300);
                set_atkCooldown(1.0f);
                set_atkDuration(0.5f);
                atkTimer = 2.0f;
                coolDownTimer = 2.5f;

                set_atkDamage(25);
                setSize(32.0f, 64.0f);
                isTraped(1.0f);

                sprite.addNewAnimation(AnimationID::walk, WALK_PATH, 7, 0.3);
                sprite.addNewAnimation(AnimationID::attack, ATACK_PATH, 7, 0.2);
                sprite.addNewAnimation(AnimationID::idle, IDLE, 7, 10);
                sprite.addNewAnimation(AnimationID::reciveDamage, HURT, 2, dmgCooldown * 2);
            }
            void Soldier::update(const float dt)
            {

                // Atualiza o archer
                incrementAtkTimer(dt);
                incrementDmgTimer(dt);
                trapTimmer += dt;

                velocity.y += GRAVITY;
                int dir;
                if (getPlayerPosition().x < getPosition().x)
                {
                    setFacing(true);
                    dir = -1;
                }
                else
                {
                    setFacing(false);
                    dir = 1;
                }

                if (updatePlayerDistance() < 100.0f)
                {
                    velocity.x = BASE_SPEED * 2 * dir;
                    execute();
                }
                else if (updatePlayerDistance() < 350.0f)
                {
                    velocity.x = BASE_SPEED * dir;
                }
                if (canMove())
                {
                    // cout << slowness << endl;

                    body->move(velocity.x * dt, velocity.y * dt);
                }
                updateSprite(dt);
                render();
            }

            void Soldier::execute()
            {
                atack();
            }

            void Soldier::toDamage(Player *pP)
            {
                if (flagIsAtking)
                {
                    pP->reciveDmg(atkDamage);
                }
                pP->isTraped(1.0f);

                if (facingLeft)
                    pP->set_velocity(TupleF(-50.0f, -10.0f));
                else
                {
                    pP->set_velocity(TupleF(50.0f, -10.0f));
                }
            }

            void Soldier::updateSprite(float dt)
            {
                TupleF pos = getPosition();
                pos(pos.x, pos.y - getSize().y / 2);
                if (!canReciveDmg())
                {
                }
                else if (isAtking())
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

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
