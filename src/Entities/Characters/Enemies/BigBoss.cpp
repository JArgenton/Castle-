#include "Entities/Characters/Enemies/BigBoss.hpp"
#include "States/Level.hpp"
#include "Utilis/geometry.hpp"

#define BOSS_SPEED 25.0f
#define ATACK_PATH "assets/Knight_2/Attack 1.png"
#define WALK_PATH "assets/Knight_2/Run.png"
#define IDLE "assets/Knight_2/Idle.png"
#define DAMAGE "assets/Knight_2/Hurt.png"
namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {

            BigBoss::BigBoss(TupleF _position) : Enemy(_position, ID::BOSS)
            {
            }
            BigBoss::~BigBoss()
            {
                pPlayer2 = nullptr;
                pPlayer1 = nullptr;
            }

            void BigBoss::setIsHitting(bool _isHitting)
            {
                flagIsHitting = _isHitting;
            }

            bool BigBoss::getIsHitting()
            {
                return flagIsHitting;
            }

            void BigBoss::setGrabTimmer(float _grabTimmer)
            {
                grabTimmer = _grabTimmer;
            }

            float BigBoss::getGrabTimmer()
            {
                return grabTimmer;
            }

            void BigBoss::setGrabCooldown(float _grabCooldown)
            {
                grabCooldown = _grabCooldown;
            }

            float BigBoss::getGrabCooldown()
            {
                return grabCooldown;
            }

            void BigBoss::setHitTimmer(float _hitTimmer)
            {
                hitTimmer = _hitTimmer;
            }

            float BigBoss::getHitTimmer()
            {
                return hitTimmer;
            }

            void BigBoss::setHitLimit(float _hitLimit)
            {
                hitLimit = _hitLimit;
            }

            float BigBoss::getHitLimit()
            {
                return hitLimit;
            }

            void BigBoss::initialize()
            {
                set_health(1500);
                body->setOutlineThickness(2.0f);
                body->setOutlineColor(sf::Color::White);
                dmgCooldown = 0.5f;
                grabCooldown = 5.0f;
                set_atkCooldown(2.0f);
                set_atkDuration(0.5f);
                hitLimit = 0.4f;

                dmgTimer = 0.0f;
                grabTimmer = 0.0f;
                atkTimer = 0.0f;
                hitTimmer = 0.0f;
                setSize(64.0f, 64.0f);

                set_atkDamage(100);

                isTraped(1.0f);
                facingLeft = true;
                setPosition(TupleF(804.0f, 1508.0f));

                sprite.addNewAnimation(AnimationID::walk, WALK_PATH, 7, 0.1);
                sprite.addNewAnimation(AnimationID::attack, ATACK_PATH, 5, 0.4);
                sprite.addNewAnimation(AnimationID::idle, IDLE, 4, 10);
                sprite.addNewAnimation(AnimationID::reciveDamage, DAMAGE, 2, 2);

                sprite.setBodyScale(2, 1.5);
            }

            void BigBoss::update(const float dt)
            {
                /*fazer funçao de carga de capacitor*/
                grabTimmer += dt;

                TupleF PlayerPosition = getPlayerPosition();

                incrementAtkTimer(dt);
                incrementDmgTimer(dt);
                trapTimmer += dt;

                if (getPlayerPosition().x < getPosition().x)
                {
                    setFacing(true);
                }
                else
                {
                    setFacing(false);
                }

                if (PlayerPosition.y < (getPosition().y + getSize().y))
                {
                    if (canMove())
                    {
                        if (facingLeft)
                        {
                            velocity.x = -BOSS_SPEED;
                        }
                        else
                        {
                            velocity.x = BOSS_SPEED;
                        }
                    }
                }

                velocity.y += GRAVITY;
                body->move(velocity.x * dt, velocity.y * dt);
                updateSprite(dt);
                render();

                execute();
            }

            void BigBoss::execute()
            {
                float playerDistance = updatePlayerDistance();

                if (canGrab())
                {
                    shoot();
                    grabTimmer = 0;
                }
                else
                {
                    if (updatePlayerDistance() < 100.0f)
                    {
                        if (flagIsHitting && updatePlayerDistance() < 75.0f)
                        {
                            isTraped(1.5f);
                            if (isP1NearestPlayer())
                            {

                                pPlayer1->reciveDmg(150);
                            }
                            else
                            {
                                pPlayer2->reciveDmg(150);
                            }
                        }
                        else
                        {
                            atack();
                        }
                    }
                }
            }

            void BigBoss::atack()
            {
                if (canAtk())
                {
                    flagIsAtking = true;
                }
            }

            void BigBoss::incrementAtkTimer(const float dt)
            {
                if (flagIsAtking)
                {
                    coolDownTimer = 0;
                    atkTimer += dt;
                    if (atkTimer > atkDuration)
                    {
                        flagIsAtking = false;
                        flagIsHitting = true;
                    }
                    body->setFillColor(sf::Color::Yellow);

                } //
                else if (flagIsHitting)
                {
                    atkTimer = 0;
                    hitTimmer += dt;
                    if (hitTimmer > hitLimit)
                    {
                        flagIsHitting = false;
                    }
                    body->setFillColor(sf::Color::Red);
                }
                else
                {
                    hitTimmer = 0;
                    coolDownTimer += dt;
                    body->setFillColor(sf::Color::Blue);
                }
            }

            void BigBoss::toDamage(Player *pP)
            {
                pP->reciveDmg(50);
            }

            bool BigBoss::canGrab()
            {
                return grabCooldown < grabTimmer;
            }

            void BigBoss::shoot()
            {
                TupleF BossPosition = getPosition();
                TupleF BossSize = getSize();
                TupleF PlayerPosition = getPlayerPosition();
                PlayerPosition.y -= 40;

                TupleF projectilePosition;

                // Calcule a posição central do arqueiro
                if (facingLeft)
                {
                    projectilePosition = TupleF(BossPosition.x - BossSize.x, BossPosition.y - BossSize.y / 2);
                }
                else
                {
                    projectilePosition = TupleF(BossPosition.x + BossSize.x, BossPosition.y - BossSize.y / 2);
                }

                TupleF direction = geometry::getDirectionalVector(projectilePosition, PlayerPosition);

                States::Level::createProjectile(projectilePosition, ID::HOOK, direction);
            }
            void BigBoss::updateSprite(float dt)
            {
                TupleF pos = getPosition();
                pos(pos.x, pos.y - getSize().y / 2);
                if (!canReciveDmg())
                {
                    sprite.update(AnimationID::reciveDamage, facingLeft, pos, dt);
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
