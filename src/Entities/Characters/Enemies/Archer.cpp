#include "Entities/Characters/Enemies/Archer.hpp"
#include "Principal.hpp"
#define ARCHER_DMG 10.0f
#define ARCHER_TIME 10.0f
#define ARCHER_ATK_COOLDOWN 20.0f
#define ARCHER_HEALTH 50
#define ARCHER_WIDGHT 30.0f
#define ARCHER_HEIGHT 70.0f
#define ARCHER_POINTS 200
#define ARCHER_RANGE 150.0f

std::string ARCHER_PATH = "assets/freetileset/png/Object/Crate.png";

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
                TupleF archerSize = getSize(); // Assume que getSize retorna o tamanho do arqueiro

                // Calcule a posição central do arqueiro
                TupleF projectilePosition = TupleF(archerPosition.x + archerSize.x / 2, archerPosition.y + archerSize.y / 2);
                Principal::createProjectile(projectilePosition, ID::ARROW);
            }

            void Archer::update(const float dt)
            {
                setPosition(TupleF(150.0f, 150.0f));

                // Atualiza o archer
                Character::incrementAtkTimer(dt);
                // Atualiza posição do archer
                TupleF position = getPosition();

                velocity.y += GRAVITY;
                position.x += velocity.x * dt;
                position.y += velocity.y * dt;
                body->move(position.x, position.y);
                render();
                if (canAtk())
                {
                    // shoot();
                }
            }

            void Archer::initialize()
            {

                body->setFillColor(sf::Color::Yellow);
                setPosition(TupleF(150.0f, 150.0f));

                set_atkDamage(ARCHER_DMG);
                setSize(50.0f, 100.0f);
                SetTexture(ARCHER_PATH);
                render();
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
