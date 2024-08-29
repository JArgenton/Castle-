#include "Entities/Characters/Enemies/Soldier.hpp"
#include "Entities/Characters/Player.hpp"
#include <math.h>

#define BASE_SPEED 55.0f
namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {

            std::string Soldier::texturepath("assets/warrior.png");

            Soldier::Soldier(TupleF _position) : Enemy(_position, ID::SOLDIER)
            {
            }
            Soldier::~Soldier()
            {
            }

            void Soldier::initialize()
            {
                dmgCooldown = 0.5f;

                set_health(500);
                set_atkCooldown(1.0f);
                set_atkDuration(0.5f);
                atkTimer = 2.0f;
                coolDownTimer = 2.5f;

                set_atkDamage(25);
                setSize(32.0f, 64.0f);
                SetTexture(texturepath);
                isTraped(1.0f);
                render();
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
                    body->move(velocity.x * dt, velocity.y * dt);
                }
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

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
