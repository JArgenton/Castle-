#include "Factories/EntityFactory.hpp"

namespace Factories
{
    class EnemiesFactory : public EntityFactory
    {
    private:
    public:
        EnemiesFactory();
        ~EnemiesFactory();
        Entity *FactoryMethood(TupleF _position, ID _id);
    };

} // namespace Factories
