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

    Utilis::Coordinates::CoordF Collision::check_collision(sf::RectangleShape *body1, sf::RectangleShape *body2)
    {
        Entity *entt1 = nullptr;
        Entity *entt2 = nullptr;
        Utilis::Coordinates::CoordF intersection;
        Utilis::Coordinates::CoordF centerDistance;
        int i, j;

        for (i = 0; i < StaticEntities->getsize(); i++)
        {
            entt1 = StaticEntities->operator[](i);
            for (j = i + 1; j < MovingEntities->getsize(); j++)
            {
                entt2 = MovingEntities->operator[](j);

                centerDistance.x = entt2->get_position().x - entt1->get_position().x;
                centerDistance.y = entt2->get_position().y - entt1->get_position().y;

                intersection.x = abs(centerDistance.x) - (entt1->get_size().x / 2.0f + entt2->get_size().x) / 2.0f;
                intersection.y = abs(centerDistance.y) - (entt1->get_size().y / 2.0f + entt2->get_size().y) / 2.0f;

                if (intersection.x < 0.0f && intersection.y < 0.0f)
                {
                    return intersection;
                }
            }
        }
        for (i = 0; i < MovingEntities->getsize(); i++)
        {
            entt1 = MovingEntities->operator[](i);
            for (j = i + 1; j < StaticEntities->getsize(); j++)
            {
                entt2 = StaticEntities->operator[](j);

                centerDistance.x = entt2->get_position().x - entt1->get_position().x;
                centerDistance.y = entt2->get_position().y - entt1->get_position().y;

                intersection.x = abs(centerDistance.x) - (entt1->get_size().x / 2.0f + entt2->get_size().x) / 2.0f;
                intersection.y = abs(centerDistance.y) - (entt1->get_size().y / 2.0f + entt2->get_size().y) / 2.0f;

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