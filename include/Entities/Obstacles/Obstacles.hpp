#pragma once
#include "Entities/Characters/Character.hpp"
namespace Entities
{
    namespace Characters
    {
        class Character;
    } // namespace Characters;

    class Obstacle : public Entity
    {
    protected:
        float forcaBloco;

    public:
        Obstacle(TupleF _position = TupleF(0.0f, 0.0f), ID _id = empty);
        virtual ~Obstacle();
        virtual void initialize() = 0;
        virtual void update(float dt) = 0;
        virtual void toObstruct(Entities::Characters::Character *pC) = 0;
        void execute() override {}
        virtual void collide(Entity *other, TupleF intersec) override {}
    };
}