#pragma once
#include <iostream>
#include "Utilis/Tuple.hpp"
#include "Ent.hpp"
using namespace std;
using namespace Tuples;

namespace Entities
{

#define GRAVITY 2.81f
    enum ID
    {
        empty = 0,
        PLAYER,
        WEAPON,
        plataforma,
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
    };
}
