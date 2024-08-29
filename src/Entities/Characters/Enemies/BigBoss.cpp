#include "Entities/Characters/Enemies/BigBoss.hpp"
#include "States/Level.hpp"
#include "Utilis/geometry.hpp"

#define BOSS_SPEED 25.0f
namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            std::string BigBoss::texturepath("assets/freetileset/png/Object/Sign_1.png");

            BigBoss::BigBoss(TupleF _position) : Enemy(_position, ID::BOSS)
            {
            }
            BigBoss::~BigBoss()
            {
                pPlayer2 = nullptr;
                pPlayer1 = nullptr;
            }
            void BigBoss::initialize()
            {
                set_health(1500);

                dmgCooldown = 0.5f;
                grabCooldown = 5.0f;
                set_atkCooldown(2.0f);
                set_atkDuration(0.5f);
                hitLimit = 0.4f;

                dmgTimer = 0.0f;
                grabTimmer = 0.0f;
                atkTimer = 0.0f;
                hitTimmer = 0.0f;

                set_atkDamage(100);

                setSize(64.0f, 80.0f);

                SetTexture(texturepath);

                isTraped(1.0f);

                render();
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

                execute();
            }

            void BigBoss::execute()
            {
                float playerDistance = updatePlayerDistance();

                if (canGrab())
                {
                    shoot();
                }
                else
                {
                    if (updatePlayerDistance() < 100.0f)
                    {
                        if (flagIsHitting)
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
                } //
                else if (flagIsHitting)
                {
                    atkTimer = 0;
                    hitTimmer += dt;
                    if (hitTimmer > hitLimit)
                    {
                        flagIsHitting = false;
                    }
                }
                else
                {
                    hitTimmer = 0;
                    coolDownTimer += dt;
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
                    projectilePosition = TupleF(BossPosition.x - BossSize.x, BossPosition.y);
                }
                else
                {
                    projectilePosition = TupleF(BossPosition.x + BossSize.x, BossPosition.y);
                }

                TupleF direction = geometry::getDirectionalVector(projectilePosition, PlayerPosition);

                States::Level::createProjectile(projectilePosition, ID::ARROW, direction);
            }

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
