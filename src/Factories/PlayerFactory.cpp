#include "Factories/PlayerFactory.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Weapons/Sword.hpp"
namespace Factories
{

    PlayerFactory::PlayerFactory()
    {
    }

    PlayerFactory::~PlayerFactory()
    {
    }
    Entity *PlayerFactory::FactoryMethood(TupleF _position, ID _id)
    {
        ID player;
        Entity *pE = nullptr;

        player = _id;
        switch (player)
        {
        case ID::PLAYER1:
        {
            Weapons::Sword *weapon = new Weapons::Sword;
            pE = new Entities::Characters::Player(_position, static_cast<Weapons::Weapon *>(weapon), PLAYER1);
            break;
        }
        case ID::PLAYER2:
        {
            Weapons::Sword *weapon = new Weapons::Sword;
            pE = new Entities::Characters::Player(_position, static_cast<Weapons::Weapon *>(weapon), PLAYER2);
            break;
        }
        default:
            break;
        }
        if (pE != nullptr)
        {
            pE->initialize();
        }
        return pE;
    }

} // namespace Factories
