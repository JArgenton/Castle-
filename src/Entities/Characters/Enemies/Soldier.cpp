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

                set_health(300);
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

                if (getPlayerPosition().x < getPosition().x)
                {
                    setFacing(true);
                }
                else
                {
                    setFacing(false);
                }

                if (updatePlayerDistance() < 100.0f)
                {
                    velocity.x *= 2;
                }
                else if (updatePlayerDistance() < 350.0f)
                {

                    float dir = getPlayerPosition().x - getPosition().x;
                    dir /= abs(dir);
                    velocity.x = BASE_SPEED * dir;
                }
                if (canMove())
                {
                    velocity.y += GRAVITY;
                    body->move(velocity.x * dt, velocity.y * dt);
                    execute();
                }
                render();
            }

            void Soldier::execute()
            {

                if (facingLeft)
                    set_velocity(TupleF(-150.0f, -150.0f));
                else
                {
                    set_velocity(TupleF(150.0f, -150.0f));
                }

                atack();
            }

            void Soldier::toDamage(Player *pP)
            {

                if (flagIsAtking)
                {
                    pP->reciveDmg(atkDamage);
                }
                isTraped(1.0f);
                pP->isTraped(1.0f);

                if (facingLeft)
                    pP->set_velocity(TupleF(-50.0f, -50.0f));
                else
                {
                    pP->set_velocity(TupleF(50.0f, -50.0f));
                }

                /*TODO -> algo diferente*/
            }

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
