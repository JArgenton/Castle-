#pragma once
#include <SFML/Graphics.hpp>
#include "Utilis/Tuple.hpp"
#include "Utilis/EntityList.hpp"
namespace managers
{
    class Collision
    {
    private:
        List::EntityList *StaticEntities;
        List::EntityList *MovingEntities;
        static Collision *instance;
        Collision(List::EntityList *StaticEntities, List::EntityList *MovingEntities);

    public:
        ~Collision();
        TupleF check_collision(sf::RectangleShape *body1, sf::RectangleShape *body2);
        void exec();
    };
}