#pragma once
#include "Entities/Entity.hpp"

namespace Entities
{
    class StaticEntity : public Entity
    {
    protected:
    public:
        static List::EntityList StaticEntities;
        StaticEntity(TupleF _position = TupleF(0.0f, 0.0f), ID _id = empty);
        virtual ~StaticEntity();
        virtual void initialize() = 0;
        void execute() override {}
        virtual void collide(Entity *other, TupleF intersec) override {}
    };
}