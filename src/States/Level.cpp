#include "States/Level.hpp"

#include "Entities/Obstacles/Plataform.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Weapons/Sword.hpp"
#include "Entities/Projectiles/Hook.hpp"

#define BACKGROUND_LEVEL1 "assets/BackGrounds/OutSideCastle.png"

using namespace GraphicalElements;

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
                                      hpDisplay1(),
                                      // hpDisplay2(),
                                      background(),
                                      obstacles(),
                                      collisionManager(&obstacles, &Level::movingEntities),
                                      pGraphicM(Managers::Graphics::get_instance()),
                                      pControl(),
                                      levelEnded(true),
                                      player1Points(10),
                                      player2Points(0)

    {
        eFactory = new Factories::EnemiesFactory;
        playerFactory = new Factories::PlayerFactory;
        oFactory = new Factories::ObstaclesFactory;
        pControl.setMachine(pStateMachine);
        background.initialize(BACKGROUND_LEVEL1, TupleF(pGraphicM->getWindowSize().x / 2.0f, pGraphicM->getWindowSize().y / 2), TupleF(pGraphicM->getWindowSize().x, pGraphicM->getWindowSize().y));
        background.render();
    }
    Level::~Level()
    {

        movingEntities.cleanList();
        obstacles.cleanList();
        if (eFactory)
            delete eFactory;
        if (playerFactory)
            delete playerFactory;
        if (oFactory)
            delete oFactory;
        eFactory = nullptr;
        playerFactory = nullptr;
        oFactory = nullptr;
        Player1 = nullptr;
        Player2 = nullptr;
    }

    TupleF Level::centerView()
    {
        TupleF centerPosition;
        if (Player1->isActive())
        {
            TupleF p1Position;
            p1Position = Player1->getPosition();
            if (Player2->isActive() && Player2->getFullyCreated())
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
        else
        {
            centerPosition = Player2->getPosition();
        }
        // pGraphicM->centerViewOn(TupleF(player1->getPosition().x, pGraphicM->getWindowSize().y / 2 - PLATFORM_HEIGHT / 2));
        return centerPosition;
    }

    void Level::update(const float dt)
    {
        background.render();
        background.update(TupleF(Player1->getPosition().x, Player1->getPosition().y));
        float healthPercentage = static_cast<float>(Player1->getHealth()) / Player1->getTotalHealth();
        hpDisplay1.update(healthPercentage, TupleF(Player1->getPosition().x - 20, Player1->getPosition().y - 50));

        // cout << Player1->getHealth() << endl;
        TupleF centerpos = centerView();
        pGraphicM->centerViewOn(centerpos);

        for (int i = 0; i < movingEntities.getSize(); i++)
        {
            movingEntities[i]->update(dt);
            if (!static_cast<MovingEntity *>(movingEntities[i])->isActive())
            {
                if (movingEntities[i]->getId() == ID::PLAYER1 || movingEntities[i]->getId() == ID::PLAYER2)
                {
                }
                else
                {

                    movingEntities.deleteEntity(i);
                }
            }
        }
        for (int i = 0; i < obstacles.getSize(); i++)
        {
            obstacles[i]->update(dt);
        }
        collisionManager.check_collision();

        if (!Player1->isActive())
        {

            if (!Player2->getFullyCreated())
            {

                endLevel();
                changeState(States::stateID::GAMEOVER);
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
        hpDisplay1.render();
    }

    void Level::resetState()
    {

        if (levelEnded)
        {
            createFase("fase1.tmj");
            levelEnded = false;
        }
    }

    Entity *Level::Create(Factories::EntityFactory *pFactory, TupleF _position, ID _id)
    {
        return pFactory->FactoryMethood(_position, _id);
    }

    void Level::createProjectile(TupleF _position, ID _id, TupleF direction)
    {
        Entity *pE = Create(&projFactory, _position, _id);
        if (_id == ARROW)
        {
            static_cast<Projectiles::Arrow *>(pE)->setDirection(direction);
        }
        else
        {
            static_cast<Projectiles::Hook *>(pE)->setDirection(direction);
        }
        if (pE)
        {
            movingEntities.add(pE);
        }
    }

    void Level::endLevel()
    {
        movingEntities.cleanList();
        obstacles.cleanList();
        levelEnded = true;
    }

    int Level::getPlayerPoints() const
    {
        if (Player1)
        {
            return Player1->getPoints();
        }
        else
        {
            std::cerr << "Player1 é nulo!" << std::endl;
            return 0; // Retorna um valor padrão ou trate o erro
        }
    }
    void Level::createFase(const std::string &path)
    {
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
        Entity *pE = nullptr;

        Player1 = static_cast<Characters::Player *>(Create(playerFactory, TupleF(164.0f, 1508.0f), ID::PLAYER1));
        if (Player1)
        {
            movingEntities.add(Player1);
            pControl.setPlayer(Player1);
            movingEntities.add(dynamic_cast<Weapons::Sword *>(Player1->get_weapon()));
        }
        Player2 = static_cast<Characters::Player *>(Create(playerFactory, TupleF(164.0f, 1508.0f), ID::PLAYER2));
        if (Player2)
        {
            movingEntities.add(Player2);
            pControl.setPlayer(Player2);
            movingEntities.add(dynamic_cast<Weapons::Sword *>(Player2->get_weapon()));
        }
        pE = Create(eFactory, TupleF(804.0f, 1508.0f), ID::BOSS);
        if (pE)
        {
            movingEntities.add(pE);

            static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player1);
            static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player2);
        }
        // iterate through the matrixa
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {

                int entityType = matrix[y * width + x];

                switch (entityType)
                {
                case 1:
                {
                    pE = Create(oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::PLATAFORM);
                    if (pE)
                    {
                        obstacles.add(pE);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }

                case 2:
                {

                    pE = Create(eFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ARCHER);
                    if (pE)
                    {
                        movingEntities.add(pE);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player1);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player2);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }
                case 3:
                {

                    pE = Create(eFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::SOLDIER);
                    if (pE)
                    {
                        movingEntities.add(pE);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player1);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player2);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }
                case 4:
                {

                    pE = Create(eFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::empty);
                    if (pE)
                    {
                        movingEntities.add(pE);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player1);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Player2);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }
                case 5:
                    // criar player falhou
                    break;
                case 6:
                {
                    pE = Create(oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::TRAP);
                    if (pE)
                    {
                        obstacles.add(pE);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }
                case 7:
                {
                    pE = Create(oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::LAVA);
                    if (pE)
                    {
                        obstacles.add(pE);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }
                case 8:
                {
                    pE = Create(oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::empty);
                    if (pE)
                    {
                        obstacles.add(pE);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }
                break;
                default:
                    break;
                }
            }
        }
    }

} // namespace States