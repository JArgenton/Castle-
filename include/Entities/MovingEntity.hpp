#pragma once
#include "GraphElements/MultiFrameAnimation.hpp"
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

        GraphicalElements::MultiFrameAnimation sprite;

    public:
        MovingEntity(TupleF _position = TupleF(0.0f, 0.0f), ID id = empty);

        virtual ~MovingEntity();

        /*SETs*/
        void set_velocity(TupleF pvelocity);
        void setFacing(bool direction);
        void setActive(bool active);

        void render();
        /*GETs*/
        TupleF getVelocity();
        int getDamage();

        /*visuals*/
        virtual void initialize() = 0; // carrega as texturas

        /*Colisions*/
        virtual void collide(Entity *other, TupleF intersec) = 0;
        virtual void moveOnColision(Entity *other, TupleF intersection);

        /*conditions*/
        bool isActive();
        bool isFacingLeft();

        /*update*/
        virtual void update(const float dt) = 0;
        // virtual void updateSprite(const float dt) = 0;
    };
}