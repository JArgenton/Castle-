#include "Entities/Characters/Enemies/Archer.hpp"
#include "States/Level.hpp"
#define ARCHER_DMG 10
#define ARCHER_TIME 10.0f
#define ARCHER_ATK_COOLDOWN 20.0f
#define ARCHER_HEALTH 50
#define ARCHER_WIDGHT 70.0f
#define ARCHER_HEIGHT 70.0f
#define ARCHER_POINTS 200
#define ARCHER_RANGE 150.0f

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
            }

            void Archer::shoot()
            {
                TupleF archerPosition = getPosition();
                TupleF archerSize = getSize();

                // Calcule a posição central do arqueiro
                TupleF projectilePosition = TupleF(archerPosition.x + archerSize.x / 2, archerPosition.y - archerSize.y / 2);
                States::Level::createProjectile(projectilePosition, ID::ARROW);
            }

            void Archer::update(const float dt)
            {

                execute();
                // Atualiza o archer
                Character::incrementAtkTimer(dt);
                // Atualiza posição do archer

                velocity.y += GRAVITY;

                body->move(velocity.x * dt, velocity.y * dt);
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

                set_health(150);
                set_atkCooldown(1.0f);
                set_atkDuration(0.5f);
                atkTimer = 2.0f;
                coolDownTimer = 2.5f;

                set_atkDamage(ARCHER_DMG);
                setSize(50.0f, 100.0f);
                SetTexture(ARCHER_PATH);

                render();
            }

            void Archer::execute()
            {
                atack();
            }

            void Archer::updateSprite(const float dt)
            {
                // TODO
            }
        }
    }
}
