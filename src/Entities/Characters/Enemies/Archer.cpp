#include "Entities/Characters/Enemies/Archer.hpp"
#include "States/Level.hpp"
#include "Utilis/geometry.hpp"
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
                TupleF pPos = getPlayerPosition();
                pPos.y -= 40;
                TupleF projectilePosition;
                // Calcule a posição central do arqueiro
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
                // Atualiza o archer
                Character::incrementAtkTimer(dt);
                incrementDmgTimer(dt);
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

                dmgCooldown = 0.5;

                set_health(150);
                set_atkCooldown(1.0f);
                set_atkDuration(0.5f);
                atkTimer = 2.0f;
                coolDownTimer = 2.5f;

                set_atkDamage(ARCHER_DMG);
                setSize(32.0f, 64.0f);
                SetTexture(ARCHER_PATH);

                render();
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
                // TODO
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
