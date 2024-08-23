#include "Entities/Characters/Enemies/Soldier.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {

            std::string Soldier::texturepath("assets/freetileset/png/Tiles/17.png");

            Soldier::Soldier(TupleF _position) : Enemy(_position)
            {
            }
            Soldier::~Soldier()
            {
            }
            void Soldier::collide(Entity *other, TupleF intersec)
            {
            }
            void Soldier::initialize()
            {
            }
            void Soldier::update(const float dt)
            {
            }
            void Soldier::execute()
            {
            }

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
