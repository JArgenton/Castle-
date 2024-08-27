#pragma once
#include <SFML/Graphics.hpp>
#include "Utilis/Tuple.hpp"
#include "Utilis/EntityList.hpp"
namespace Managers
{
    class Collision
    {
    private:
        List::EntityList *StaticEntities;
        List::EntityList *MovingEntities;

    public:
        Collision(List::EntityList *_staticEntities, List::EntityList *_movingEntities);
        ~Collision();
        void check_collision();
    };
}