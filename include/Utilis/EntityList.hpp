#include "Entities/Entity.hpp"
#include "Utilis/ListTemplate.hpp"
namespace List
{
    class EntityList
    {
    private:
        List<Entities::Entity> list;

    public:
        EntityList();
        ~EntityList();
        void add(Entities::Entity *pE);
        Entities::Entity *remove(Entities::Entity *pE);
        Entities::Entity *remove(int index);
        void deleteEntity(Entities::Entity *pE);
        void deleteEntity(int index);
        int getSize();
        Entities::Entity *operator[](int index);
        void cleanList();
    }; // Class EntityList baseada na classe de mesmo nome do monitor Burda

}
