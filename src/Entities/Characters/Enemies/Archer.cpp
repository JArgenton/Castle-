#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Weapons/Projectile.hpp"
#include <iostream>
#include <cmath>

#define ARCHER_DMG 10.0f
#define ARCHER_TIME 10.0f
#define ARCHER_ATK_COOLDOWN 20.0f
#define ARCHER_HEALTH 50
#define ARCHER_WIDGHT 30
#define ARCHER_HEIGHT 70
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
                : Enemy(position, ARCHER, ARCHER_HEALTH, pP, ARCHER_ATK_COOLDOWN, ARCHER_TIME, ARCHER_POINTS), timer(0.0)
            {
                set_atkDamage(ARCHER_DMG);
            }

            Archer::~Archer()
            {
            }

            void Archer::shoot()
            {
                TupleF archerPosition = getPosition();
                TupleF archerSize = getSize();

                // Calcule a posição central do arqueiro
                TupleF projectilePosition = {
                    archerPosition.x - archerSize.x / 2.0f,
                    archerPosition.y - archerSize.y / 2.0f};

                // Mira no jogador
                TupleF playerPosition = pPlayer->getPosition();

                // Calcule a direção do projétil para o jogador
                float dx = playerPosition.x - projectilePosition.x;
                float dy = playerPosition.y - projectilePosition.y;
                float distance = sqrt(dx * dx + dy * dy);

                // Normaliza a direção
                TupleF direction = {dx / distance, dy / distance};

                // Define a velocidade do projétil
                float projectileSpeedX = 8.0f;
                float projectileSpeedY = 15.0f;

                TupleF projectileVelocity = {direction.x * projectileSpeedX, direction.y * projectileSpeedY};
                sf::Color projectileColor = sf::Color::Blue; // Cor do projétil

                // Cria um novo projétil
                Projectile newProjectile(projectilePosition, projectileVelocity, projectileColor);

                // Adiciona o projétil à lista de projéteis
                addProjectile(newProjectile);
            }

            void Archer::addProjectile(const Projectile &projectile)
            {
                projectiles.push_back(projectile);
            }

            void Archer::update(const float dt)
            {
                timer += dt;

                if (timer >= ARCHER_ATK_COOLDOWN)
                {
                    shoot();
                    timer = 0.0f;
                }
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
                velocity.y += (GRAVITY);
                position.x += velocity.x * dt;
                position.y += velocity.y * dt;
                setPosition(position);
                render();
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

            const std::vector<Projectile> &Archer::getProjectiles() const
            {
                return projectiles;
            }

            void Archer::updateSprite(const float dt)
            {
                // TODO
            }
        }
    }
}
