#include "Entities/Characters/Enemies/Dumb.hpp"

namespace Entities
{
    namespace Characters
    {
        namespace Enemies
        {
            static std::string texturepath("");

            Dumb::Dumb(TupleF _position) : Enemy(_position, ID::DUMB)
            {
            }
            Dumb::~Dumb()
            {
            }
            void Dumb::collide(Entity *other, TupleF intersec)
            {
            }
            void Dumb::initialize()
            {
            }
            void Dumb::update(const float dt)
            {
            }
            void Dumb::execute()
            {
            }
            void Dumb::toDamage(Player *pP)
            {
            }

        } // namespace Enemies

    } // namespace Characters

} // namespace Entities
