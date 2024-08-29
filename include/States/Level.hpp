#pragma once
// Estados
#include "States/State.hpp"
#include "States/StateMachine.hpp"

// Elementos Graficos
#include "GraphElements/StaticAnimation.hpp"
#include "GraphElements/HealthBar.hpp"
using namespace GraphicalElements;

// Gerenciadores
#include "Managers/ColisionManager.hpp"
#include "Managers/GraphicManager.hpp"

// Fabricas
#include "Factories/ProjectilesFactory.hpp"
#include "Factories/EnemiesFactory.hpp"
#include "Factories/ObstaclesFactory.hpp"
#include "Factories/PlayerFactory.hpp"

// Entidades
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemy.hpp"

// Utilitarios
#include "Utilis/EntityList.hpp"
#include "Utilis/Tuple.hpp"

#include "Control/PlayerControl.hpp"

// Criaçao de fase .json/.tmj
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace States
{

    class Level : public State
    {
    private:
        Factories::EnemiesFactory *eFactory;
        Factories::PlayerFactory *playerFactory;
        Factories::ObstaclesFactory *oFactory;
        static Factories::ProjectilesFactory projFactory;

        Characters::Player *Player1;
        Characters::Player *Player2;

        GraphicalElements::StaticAnimation background;

        static List::EntityList movingEntities;
        List::EntityList obstacles;

        Managers::Collision collisionManager;
        Managers::Graphics *pGraphicM;

        Control::PlayerControl pControl;

        HealthBar hpDisplay1;
        HealthBar hpDisplay2;

        bool backgroundRendered;

        bool levelEnded;
        int player1Points;
        int player2Points;
        TupleF nextPositionToRender;

    public:
        Level(StateMachine *pSM = nullptr);

        ~Level();

        void update(const float dt);

        void createFase(const std::string &path);

        static void createProjectile(TupleF _position, ID _id, TupleF direction);

        static Entity *Create(Factories::EntityFactory *pFactory, TupleF _position, ID _id = empty);

        void render();

        void resetState();

        void endLevel();

        int getPlayerPoints() const;

        TupleF centerView();

        void saveGameState(const std::string &filePath);

        void loadGameState(const std::string &filePath);
    };

} // namespace States
