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

                set_atkDamage(45);
                setSize(32.0f, 64.0f);
                SetTexture(texturepath);

                render();
            }
            void Soldier::update(const float dt)
            {

                updatePlayerDistance();
                // Atualiza o archer
                incrementAtkTimer(dt);
                incrementDmgTimer(dt);

                velocity.y += GRAVITY;

                body->move(velocity.x * dt, velocity.y * dt);
                execute();
                render();
                if (getPlayerDistance() < 600.0f)
                {
                    float dir = getPlayerPosition().x - getPosition().x;
                    dir /= abs(dir);
                    velocity.x = BASE_SPEED * dir;

                    if (getPlayerDistance() < 300.0f)
                    {
                        velocity.x = BASE_SPEED * dir * 2;
                        body->move(velocity.x * dt, velocity.y * dt);
                    }
                }
            }

            void Soldier::execute()
            {
            }

            void Soldier::toDamage(Player *pP)
            {
                int dmg = 10 * rand() % 3;
                pP->reciveDmg(dmg);
                /*TODO -> algo diferente*/
            }

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
