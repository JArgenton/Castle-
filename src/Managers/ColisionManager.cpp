#include "Entities/Entity.hpp"
#include "Managers/ColisionManager.hpp"
using namespace Entities;
namespace managers
{

    Collision::Collision(List::EntityList *StaticEntities, List::EntityList *MovingEntities) : StaticEntities(StaticEntities),
                                                                                               MovingEntities(MovingEntities)
    {
    }

    Collision::~Collision()
    {
        StaticEntities = nullptr;
        MovingEntities = nullptr;
    }

    TupleF Collision::check_collision(sf::RectangleShape *body1, sf::RectangleShape *body2)
    {
        Entity *entt1 = nullptr;
        Entity *entt2 = nullptr;
        TupleF intersection;
        TupleF centerDistance;
        int i, j;

        for (i = 0; i < StaticEntities->getSize(); i++)
        {
            entt1 = StaticEntities->operator[](i);
            for (j = i + 1; j < MovingEntities->getSize(); j++)
            {
                entt2 = MovingEntities->operator[](j);

                centerDistance.x = entt2->getPosition().x - entt1->getPosition().x;
                centerDistance.y = entt2->getPosition().y - entt1->getPosition().y;

                intersection.x = abs(centerDistance.x) - (entt1->getSize().x / 2.0f + entt2->getSize().x) / 2.0f;
                intersection.y = abs(centerDistance.y) - (entt1->getSize().y / 2.0f + entt2->getSize().y) / 2.0f;

                if (intersection.x < 0.0f && intersection.y < 0.0f)
                {
                    return intersection;
                }
            }
        }
        for (i = 0; i < MovingEntities->getSize(); i++)
        {
            entt1 = MovingEntities->operator[](i);
            for (j = i + 1; j < StaticEntities->getSize(); j++)
            {
                entt2 = StaticEntities->operator[](j);

                centerDistance.x = entt2->getPosition().x - entt1->getPosition().x;
                centerDistance.y = entt2->getPosition().y - entt1->getPosition().y;

                intersection.x = abs(centerDistance.x) - (entt1->getSize().x / 2.0f + entt2->getSize().x) / 2.0f;
                intersection.y = abs(centerDistance.y) - (entt1->getSize().y / 2.0f + entt2->getSize().y) / 2.0f;

                if (intersection.x < 0.0f && intersection.y < 0.0f)
                {
                    /*TODO*/
                    // entt2->collide(entt1, intersect);
                    // entt1->collide(entt2, intersect);
                }
            }
        }
    }

}