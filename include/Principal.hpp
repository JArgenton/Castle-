#pragma once

#include "Factories/EnemiesFactory.hpp"
#include "Factories/ObstaclesFactory.hpp"
#include "Factories/PlayerFactory.hpp"

#include "Managers/ColisionManager.hpp"
#include "Managers/GraphicManager.hpp"
#include "Managers/EventsManager.hpp"

#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemy.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"

#include "Utilis/EntityList.hpp"

#include "Menus/MainMenu.hpp"

#include "States/StateMachine.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include "Factories/ProjectilesFactory.hpp"

using json = nlohmann::json;

class Principal
{
private:
    Factories::EnemiesFactory *eFactory;
    Factories::PlayerFactory *playerFactory;
    Factories::ObstaclesFactory *oFactory;
    static Factories::ProjectilesFactory projFactory;
    Characters::Player *Player1;
    Characters::Player *Player2;
    static List::EntityList MovingEntities;
    List::EntityList StaticEntities;
    Managers::Collision ClManager;
    Managers::Graphics *gpManager;

public:
    Principal();
    ~Principal();
    void exec();
    void createFase(const std::string &path);
    static void createProjectile(TupleF _position, ID _id);
    static Entity *Create(Factories::EntityFactory *pFactory, TupleF _position, ID _id = empty);
};
