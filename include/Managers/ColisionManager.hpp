#pragma once
#include <SFML/Graphics.hpp>
#include "Math/Tuple.hpp"
#include "Lists/EntityList.hpp"
namespace Managers
{
    class Collision
    {
    private:
        List::EntityList *Obstacles;
        List::EntityList *MovingEntities;

    public:
        Collision(List::EntityList *_staticEntities, List::EntityList *_movingEntities);
        ~Collision();
        void check_collision();
    };
}