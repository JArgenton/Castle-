#include "Entities/Obstacles/Obstacles.hpp"

namespace Entities
{

    Obstacle::Obstacle(TupleF _position, ID _id) : Entity(_position, _id)
    {
        forcaBloco = -GRAVITY;
    }
    Obstacle::~Obstacle()
    {
    }
} // fim namespace Entities