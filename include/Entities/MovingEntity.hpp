#pragma once

#include "Entity.hpp"
using namespace Tuples;
namespace Entities
{
    class MovingEntity : public Entity
    {
    protected:
        /*geral info*/
        TupleF velocity;
        /*Flags*/
        bool active;
        bool facingLeft;

        int animationId;

    public:
        MovingEntity(TupleF _position = TupleF(0.0f, 0.0f), ID id = empty);

        virtual ~MovingEntity();

        /*SETs*/
        void set_velocity(TupleF pvelocity);
        void setFacing(bool direction);

        /*GETs*/
        TupleF get_velocity();
        ID get_id();
        int getDamage();

        /*visuals*/
        virtual void initialize(); // carrega as texturas

        /*Colisions*/
        virtual void colide(Entity *other, TupleF intersec) = 0;
        virtual void moveOnColision(Entity *other) = 0; /*TODO classe Entity other*/

        /*conditions*/
        bool isActive();
        bool isFacingLeft();

        /*update*/
        virtual void update(const float dt) = 0;
        virtual void updateSprite(const float dt) = 0;
    };
}