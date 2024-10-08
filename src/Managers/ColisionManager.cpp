#include "Entities/Entity.hpp"
#include "Managers/ColisionManager.hpp"
#include "Entities/MovingEntity.hpp"
#include "Entities/Obstacles/Obstacles.hpp"
using namespace Entities;
namespace Managers
{
    /*CLASSE INSPIRADA NA IMPLEMENTAÇAO DO MONITOR BURDA, MAS COM AS DEVIDAS MODIFICAÇOES*/

    Collision::Collision(List::EntityList *_staticEntities, List::EntityList *_movingEntities) : Obstacles(_staticEntities),
                                                                                                 MovingEntities(_movingEntities)
    {
    }

    Collision::~Collision()
    {
        Obstacles = nullptr;
        MovingEntities = nullptr;
    }

    void Collision::check_collision()
    {
        Entity *entity1 = nullptr;
        Entity *entity2 = nullptr;
        TupleF intersection;
        TupleF centerDistance;
        int i, j;

        for (i = 0; i < Obstacles->getSize(); i++)
        {
            entity1 = Obstacles->operator[](i);
            for (j = 0; j < MovingEntities->getSize(); j++)
            {

                entity2 = MovingEntities->operator[](j);

                centerDistance.x = entity2->getPosition().x - entity1->getPosition().x;
                centerDistance.y = entity2->getPosition().y - entity1->getPosition().y;

                intersection.x = abs(centerDistance.x) - (entity1->getSize().x / 2.0f + entity2->getSize().x / 2.0f);
                intersection.y = abs(centerDistance.y) - (entity1->getSize().y / 2.0f + entity2->getSize().y / 2.0f);

                if (intersection.x < 0.0f && intersection.y < 0.0f)
                {
                    entity2->collide(entity1, intersection);
                }
            }
        }
        for (i = 0; i < MovingEntities->getSize(); i++)
        {
            entity1 = MovingEntities->operator[](i);
            for (j = i + 1; j < MovingEntities->getSize(); j++)
            {
                entity2 = MovingEntities->operator[](j);

                centerDistance.x = entity2->getPosition().x - entity1->getPosition().x;
                centerDistance.y = entity2->getPosition().y - entity1->getPosition().y;

                intersection.x = abs(centerDistance.x) - (entity1->getSize().x / 2.0f + entity2->getSize().x / 2.0f);
                intersection.y = abs(centerDistance.y) - (entity1->getSize().y / 2.0f + entity2->getSize().y / 2.0f);

                if (intersection.x < 0.0f && intersection.y < 0.0f)
                {
                    entity2->collide(entity1, intersection);
                    entity1->collide(entity2, intersection);
                }
            }
        }
    }

}