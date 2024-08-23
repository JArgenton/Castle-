#include "Entities/Characters/Enemies/Archer.hpp"

#define ARCHER_DMG 10.0f
#define ARCHER_TIME 10.0f
#define ARCHER_ATK_COOLDOWN 50.0f
#define ARCHER_HEALTH 50
#define ARCHER_WIDGHT 30
#define ARCHER_HEIGHT 60
#define ARCHER_POINTS 200
#define ARCHER_RANGE 150.0f

string ARCHER_PATH = "assets/freetileset/png/Object/Crate.png";

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            Archer::Archer(TupleF position, Player *pP) : Enemy(position, ARCHER, ARCHER_HEALTH, pP, ARCHER_ATK_COOLDOWN, ARCHER_TIME, ARCHER_POINTS)
            {
                initialize();
                set_atkDamage(ARCHER_DMG);
            }

            Archer::~Archer()
            {
            }

            void Archer::update(const float dt)
            {

                Character::incrementAtkTimer(dt);

                playerDistance = getPlayerPosition().x - getPosition().x;

                MovingEntity::setFacing(1);

                if (!Character::isAtking())
                {

                    velocity.x *= 0.3;

                    if (Character::canAtk() && (abs(playerDistance) < ARCHER_RANGE))
                    {
                    }
                }
            }

            void Archer::initialize()
            {
                setSize(ARCHER_WIDGHT, ARCHER_HEIGHT);
                SetTexture(ARCHER_PATH);
            }
        }
    }
}