#include "Factories/EntityFactory.hpp"

namespace Factories
{
    class PlayerFactory : public EntityFactory
    {
    private:
    public:
        PlayerFactory();
        ~PlayerFactory();
        Entity *FactoryMethood(TupleF _position, ID _id = empty);
    };

} // namespace Factories
