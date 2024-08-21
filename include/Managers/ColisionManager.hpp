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
        static Collision *instance;
        Collision();

    public:
        ~Collision();
        void check_collision();
        static Collision *getInstance();
    };
}