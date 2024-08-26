#include "Factories/EnemiesFactory.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Characters/Enemies/Soldier.hpp"
#include "Entities/Characters/Enemies/Dumb.hpp"
#include "Principal.hpp"
namespace Factories
{
    EnemiesFactory::EnemiesFactory(List::EntityList *_StaticEntities, List::EntityList *_MovingEntities) : EntityFactory(_StaticEntities, _MovingEntities)
    {
    }

    EnemiesFactory::~EnemiesFactory()
    {
    }
    void EnemiesFactory::setPlayer(Characters::Player *pP)
    {
        pPlayer = pP;
    }
    Entity *EnemiesFactory::FactoryMethood(TupleF _position, ID _id)
    {
        ID enemy;
        if (_id == empty)
        {
            time_t t;
            srand((unsigned)time(&t));
            unsigned int randomId = (rand() % 3) + 1;
            enemy = ID(randomId);
        }
        enemy = _id;

        Entity *pE = nullptr;
        switch (enemy)
        {
        case ID::SOLDIER:
            pE = new Characters::Enemies::Soldier(_position);

            break;
        case ID::ARCHER:
            pE = new Characters::Enemies::Archer(_position);

            break;
        case ID::DUMB:
            pE = new Characters::Enemies::Dumb(_position);
            break;

        default:
            break;
        }
        if (pPlayer)
            static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(pPlayer);
        if (pE)
        {

            pE->initialize();
        }
        return pE;
    }

} // namespace Factories
