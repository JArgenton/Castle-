#include "Utilis/EntityList.hpp"
#include "Entities/Entity.hpp"
namespace List
{
    EntityList::EntityList() {}

    EntityList::~EntityList()
    {
        cleanList();
    }

    void EntityList::add(Entities::Entity *pE)
    {
        if (pE)
        {
            list.push(pE);
        }
        else
        {
            std::cout << "pE nulo, nao foi possivel inserir" << std::endl;
        }
    }

    Entities::Entity *EntityList::remove(Entities::Entity *pE)
    {
        return list.pop(pE);
    }

    Entities::Entity *EntityList::remove(int index)
    {
        return list.pop(index);
    }

    void EntityList::deleteEntity(Entities::Entity *pE)
    {
        Entities::Entity *entity = remove(pE);
        if (entity != nullptr)
        {
            delete entity;
        }
    }

    void EntityList::deleteEntity(int index)
    {
        Entities::Entity *entity = remove(index);
        if (entity)
        {
            delete entity;
        }
    }

    int EntityList::getSize()
    {
        return list.getsize();
    }

    Entities::Entity *EntityList::operator[](int index)
    {
        return list[index];
    }

    void EntityList::cleanList()
    {
        while (getSize() > 0)
        {
            deleteEntity(0);
        }
    }

}
