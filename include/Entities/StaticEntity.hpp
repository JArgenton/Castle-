#include "Entities/Entity.hpp"

namespace Entities
{

    class StaticEntity : public Entity
    {
    protected:
        GraphicBodies::StaticBody image;

    public:
        StaticEntity(Coordinates::CoordF _position = Coordinates::CoordF(0.0f, 0.0f), ID _id = empty);
        virtual ~StaticEntity();
        void render();
        virtual void update(float dt) override {}                                    //"morre" update
        virtual void colide(Entity *other, Coordinates::CoordF intersec) override {} // entidades estaticas nao terao açoes ao colidirem
        virtual void initialize() = 0;
        void moveOnColision(Entity *other) override {}
    };
}