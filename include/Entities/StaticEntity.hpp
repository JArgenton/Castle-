#include "Entities/Entity.hpp"

namespace Entities
{

    class StaticEntity : Entity
    {
    private:
        GraphicBodies::StaticBody image;

    protected:
        StaticEntity(Coordinates::CoordF _position = Coordinates::CoordF(0.0f, 0.0f), ID _id = empty);
        virtual ~StaticEntity();
        void render();
        virtual void update(float dt) override {}                                    //"morre" update
        virtual void colide(Entity *other, Coordinates::CoordF intersec) override {} // entidades estaticas nao terao açoes ao colidirem
        virtual void initialize() = 0;
    };
}