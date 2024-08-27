#include "States/Level.hpp"

#include "Entities/Obstacles/Plataforma.hpp"

namespace States
{
    Factories::ProjectilesFactory Level::projFactory;
    List::EntityList Level::movingEntities;

    Level::Level(StateMachine *pSM) : State(pSM, stateID::FASE),
                                      eFactory(),
                                      playerFactory(),
                                      oFactory(),

                                      Player1(),
                                      Player2(),
                                      background(),
                                      staticEntities(),
                                      collisionManager(&staticEntities, &Level::movingEntities),
                                      pGraphicM(Managers::Graphics::get_instance()),
                                      pControl(),
                                      levelEnded(false),
                                      playerPoints(0)

    {
        eFactory = new Factories::EnemiesFactory;
        playerFactory = new Factories::PlayerFactory;
        oFactory = new Factories::ObstaclesFactory;
    }
    Level::~Level()
    {
        if (eFactory)
            delete eFactory;
        if (playerFactory)
            delete playerFactory;
        if (oFactory)
            delete oFactory;
        if (Player1)
        {
            delete Player1;
        }
        if (Player2)
        {
            delete Player2;
            Player2 = nullptr;
        }
        eFactory = nullptr;
        playerFactory = nullptr;
        oFactory = nullptr;
        Player1 = nullptr;
        movingEntities.cleanList();
        staticEntities.cleanList();
    }

    TupleF Level::centerView()
    {
        TupleF centerPosition;
        if (Player1)
        {
            TupleF p1Position;
            p1Position = Player1->getPosition();
            if (Player2)
            {
                TupleF p2Position;
                p2Position = Player2->getPosition();

                centerPosition((p1Position.x + p2Position.x) / 2, (p1Position.y + p2Position.y) / 2);
            }
            else
            {
                centerPosition = p1Position;
            }
        }
        // pGraphicM->centerViewOn(TupleF(player1->getPosition().x, pGraphicM->getWindowSize().y / 2 - PLATFORM_HEIGHT / 2));
        return centerPosition;
    }

    void Level::update(const float dt)
    {

        TupleF centerpos = centerView();
        pGraphicM->centerViewOn(centerpos);

        for (int i = 0; i < movingEntities.getSize(); i++)
        {

            static_cast<MovingEntity *>(movingEntities[i])->update(dt);
            if (!static_cast<MovingEntity *>(movingEntities[i])->isActive())
            {
                movingEntities.deleteEntity(i);
            }
        }
        collisionManager.check_collision();

        background.update(centerpos);

        if (!Player1->isActive())
        {
            if (!Player2)
            {
                endLevel();
            }
            else if (!Player2->isActive())
            {
                endLevel();
            }
        }
        // Atualiza a janela
    }

    void Level::render()
    {

        background.render();

        for (int i = 0; i < staticEntities.getSize(); i++)
        {
            staticEntities[i]->render();
        }
    }

    void Level::resetState()
    {
        createFase("map.tmj");
    }

    Entity *Level::Create(Factories::EntityFactory *pFactory, TupleF _position, ID _id)
    {
        return pFactory->FactoryMethood(_position, _id);
    }

    void Level::createProjectile(TupleF _position, ID _id)
    {
        Entity *pE = Create(&projFactory, _position, _id);

        if (pE)
        {
            movingEntities.add(pE);
        }
    }

    void Level::endLevel()
    {
        // playerPoints = player->getPlayerPoints();
        movingEntities.cleanList();
        staticEntities.cleanList();
        levelEnded = true;
    }

    int Level::getPlayerPoints() const
    {
        return playerPoints;
    }
    void Level::createFase(const std::string &path)
    {
        string texturepath = "assets/freetileset/png/BG/BG.png";
        background.SetTexture(texturepath);
        std::ifstream file(path);
        json tmjData;
        file >> tmjData;

        // tamanho de cada bloco
        int tileWidth = tmjData["tilewidth"];
        int tileheight = tmjData["tileheight"];

        auto layer = tmjData["layers"][0];
        auto matrix = layer["data"];
        int width = layer["width"];
        int height = layer["height"];

        Player1 = static_cast<Characters::Player *>(Create(playerFactory, TupleF(300.0f, 270.0f), ID::PLAYER1));
        if (Player1)
        {
            movingEntities.add(Player1);
            pControl.setPlayer(Player1);
        }
        Entity *pE = Create(eFactory, TupleF(200.0f, 260.0f), ARCHER);
        if (pE)
        {
            movingEntities.add(pE);
            static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player1);
        }

        // iterate through the matrix
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int entityType = matrix[y * width + x];
                if (entityType != 0)
                {
                    staticEntities.add(Create(oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::PLATAFORMA));
                }
            }
        }
    }

} // namespace States
