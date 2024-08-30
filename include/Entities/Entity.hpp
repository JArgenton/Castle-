#pragma once

#include <iostream>
#include "Utilis/Tuple.hpp"
#include "Ent.hpp"
#include "Utilis/EntityList.hpp"

using namespace Tuples;

namespace Entities
{

#define GRAVITY 6.0f
    enum ID
    {
        empty = 0,
        PLAYER1,   // 1
        PLAYER2,   // 2
        WEAPON,    // 3
        LAVA,      // 4
        PLATAFORM, // 5
        TRAP,      // 6
        ENEMY,     // 7
        ARCHER,    // 8
        ARROW,     // 9
        SOLDIER,   // 10
        DUMB,      // 11
    };
    class Entity : public Ent
    {

    protected:
        ID id;

    public:
        Entity(TupleF = TupleF(0.0f, 0.0f), ID id = empty);

        virtual ~Entity();

        /*SETs*/
        void setPosition(TupleF _position);
        void setSize(float height, float width);

        /*GETs*/
        TupleF getSize();
        TupleF getPosition();
        ID getId();
        /*visuals*/
        virtual void initialize() = 0; // carrega as texturas
        virtual void update(float dt) = 0;
        virtual void collide(Entity *other, TupleF intersec) = 0;
    };
}
