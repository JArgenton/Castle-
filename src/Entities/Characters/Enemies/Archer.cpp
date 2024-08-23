#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Weapons/Projectile.hpp"

#define ARCHER_DMG 10.0f
#define ARCHER_TIME 10.0f
#define ARCHER_ATK_COOLDOWN 50.0f
#define ARCHER_HEALTH 50
#define ARCHER_WIDGHT 100
#define ARCHER_HEIGHT 60
#define ARCHER_POINTS 200
#define ARCHER_RANGE 150.0f

std::string ARCHER_PATH = "assets/freetileset/png/Object/Crate.png";

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            Archer::Archer(TupleF position, Player *pP)
                : Enemy(position, ARCHER, ARCHER_HEALTH, pP, ARCHER_ATK_COOLDOWN, ARCHER_TIME, ARCHER_POINTS)
            {
                set_atkDamage(ARCHER_DMG);
            }

            Archer::~Archer()
            {
            }

            void Archer::shoot()
            {
                if (pPlayer)
                {
                    TupleF playerPos = pPlayer->getPosition();
                    TupleF archerPos = getPosition();
                    TupleF direction = {(playerPos.x - archerPos.x) / 100.0f, (playerPos.y - archerPos.y) / 100.0f};

                    // Cria um novo projétil
                    Projectile newProjectile(archerPos, direction, sf::Color::Red);
                    projectiles.push_back(newProjectile);
                }
            }

            void Archer::update(const float dt)
            {
                // Atualiza o archer
                Character::incrementAtkTimer(dt);

                // Atualiza projéteis
                for (auto &projectile : projectiles)
                {
                    projectile.update(dt);
                }

                // Remove projéteis inativos
                projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile &p)
                                                 { return !p.isActive(); }),
                                  projectiles.end());

                // Atualiza posição do archer
                TupleF position = getPosition();
                velocity.y += GRAVITY;
                position.x += velocity.x * dt;
                position.y += velocity.y * dt;
                setPosition(position);
            }

            void Archer::initialize()
            {
                setSize(ARCHER_WIDGHT, ARCHER_HEIGHT);
                SetTexture(ARCHER_PATH);
            }

            void Archer::execute()
            {
                // TODO
            }

            void Archer::updateSprite(const float dt)
            {
                // TODO
            }
        }
    }
}
