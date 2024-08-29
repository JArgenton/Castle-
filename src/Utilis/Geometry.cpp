#include "Utilis/geometry.hpp"

namespace geometry
{

    void NormalizeVector(TupleF *Vector)
    {
        float norm = sqrt(pow(Vector->x, 2) + pow(Vector->y, 2));
        Vector->operator()(Vector->x / norm, Vector->y / norm);
    }
    void escalateVector(TupleF *Vector, float scale)
    {
        Vector->operator()(Vector->x * scale, Vector->y * scale);
    }
    TupleF getDirectionalVector(TupleF origin, TupleF target)
    {
        TupleF Vector;

        Vector(target.x - origin.x, target.y - origin.y);

        NormalizeVector(&Vector);

        return Vector;
    }
}
