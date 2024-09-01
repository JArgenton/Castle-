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
    protected:
        static Factories::EnemiesFactory eFactory;
        static Factories::PlayerFactory playerFactory;
        static Factories::ObstaclesFactory oFactory;
        static Factories::ProjectilesFactory projFactory;

        static Characters::Player *Player1;
        static Characters::Player *Player2;

        GraphicalElements::StaticAnimation background;

        static List::EntityList movingEntities;
        List::EntityList obstacles;

        Managers::Collision collisionManager;
        Managers::Graphics *pGraphicM;

        static Control::PlayerControl pControl;

        HealthBar hpDisplay1;
        HealthBar hpDisplay2;

        bool backgroundRendered;

        bool levelEnded;
        int player1Points;
        int player2Points;

        TupleF nextPositionToRender;

    public:
        /*ALL LEVEL METHOODS*/
        Level(StateMachine *pSM, stateID _id);
        virtual ~Level();
        static void createProjectile(TupleF _position, ID _id, TupleF direction);
        static Entity *Create(Factories::EntityFactory *pFactory, TupleF _position, ID _id = empty);
        void render();
        TupleF centerView();
        int getPlayerPoints() const;
        virtual void update(const float dt);
        void loadEnemiesFromJson(const std::string &filePath, Characters::Player *pP1, Characters::Player *pP2);
        bool getEnded();

        /*Especific level Methods*/
        virtual void createFase(const std::string &path) = 0;
        virtual void resetState() = 0;
        virtual void endLevel() = 0;
        virtual void clearState() = 0;
        // funções usadas para salvar level
        // virtual void saveGameState(const std::string &filePath);
        // virtual void loadGameState(const std::string &filePath);
        virtual void executar();
    };

} // namespace States
