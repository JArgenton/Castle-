#include "Entities/Characters/Enemies/Archer.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {

            std::string Archer::texturepath("assets/freetileset/png/Tiles/17.png");

            Archer::Archer(TupleF _position) : Enemy(_position)
            {
            }
            Archer::~Archer()
            {
            }
            void Archer::collide(Entity *other, TupleF intersec)
            {
            }
            void Archer::initialize()
            {
            }
            void Archer::update(const float dt)
            {
            }
            void Archer::execute()
            {
            }

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
