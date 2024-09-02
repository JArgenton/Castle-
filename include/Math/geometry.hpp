#include <math.h>
#include "Math/Tuple.hpp"
using namespace Tuples;
namespace geometry
{

    void NormalizeVector(TupleF *Vector);
    void escalateVector(TupleF *Vector, float scale);
    TupleF getDirectionalVector(TupleF origin, TupleF target);

}
