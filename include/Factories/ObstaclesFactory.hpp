#include "Factories/EntityFactory.hpp"

namespace Factories
{
    class ObstaclesFactory : public EntityFactory
    {
    private:
    public:
        ObstaclesFactory(/* args */);
        ~ObstaclesFactory();
        Entity *FactoryMethood(TupleF _position, ID _id = empty);
    };

} // namespace Factories
