#include "States/Level.hpp"

#include "Entities/Obstacles/Plataform.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Weapons/Sword.hpp"

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
                                      hpDisplay2(),
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
        if (!Player2->getFullyCreated())
        {
            background.update(TupleF(Player1->getPosition().x, Player1->getPosition().y));
        }
        else
        {
            background.update(TupleF((Player1->getPosition().x + Player2->getPosition().x) / 2, (Player1->getPosition().y + Player2->getPosition().y) / 2));
        }

        float healthPercentage = static_cast<float>(Player1->getHealth()) / Player1->getTotalHealth();
        hpDisplay1.update(healthPercentage, TupleF(Player1->getPosition().x - 20, Player1->getPosition().y - 50));

        if (Player2 && Player2->isActive())
        {
            float healthPercentage2 = static_cast<float>(Player2->getHealth()) / Player2->getTotalHealth();
            hpDisplay2.update(healthPercentage2, TupleF(Player2->getPosition().x - 20, Player2->getPosition().y - 50));
        }

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

        if (Player2 && Player2->isActive())
        {
            hpDisplay2.render();
        }
    }

    void Level::resetState()
    {

        if (levelEnded)
        {
            createFase("fase1.tmj");
            levelEnded = false;
        }
    }

    bool Level::setLevelEnded(bool troca)
    {
        levelEnded = troca;
    }
    Entity *Level::Create(Factories::EntityFactory *pFactory, TupleF _position, ID _id)
    {
        return pFactory->FactoryMethood(_position, _id);
    }

    void Level::createProjectile(TupleF _position, ID _id, TupleF direction)
    {
        Entity *pE = Create(&projFactory, _position, _id);
        static_cast<Projectiles::Arrow *>(pE)->setDirection(direction);
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

        // iterate through the matrixa
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Entity *pE = nullptr;

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
#include <nlohmann/json.hpp>
#include <fstream>

    using json = nlohmann::json;

#include <nlohmann/json.hpp>
#include <fstream>

    using json = nlohmann::json;

    void Level::saveGameState(const std::string &filePath)
    {
        json j;

        // Salvar estado dos jogadores
        if (Player1)
        {
            j["Player1"]["position"]["x"] = Player1->getPosition().x;
            j["Player1"]["position"]["y"] = Player1->getPosition().y;
            j["Player1"]["health"] = Player1->getHealth();
            j["Player1"]["points"] = Player1->getPoints();
        }

        if (Player2)
        {
            j["Player2"]["position"]["x"] = Player2->getPosition().x;
            j["Player2"]["position"]["y"] = Player2->getPosition().y;
            j["Player2"]["health"] = Player2->getHealth();
            j["Player2"]["points"] = Player2->getPoints();
        }

        // Salvar estado dos obstáculos
        for (int i = 0; i < obstacles.getSize(); ++i)
        {
            auto o = obstacles[i];
            json obstacle;
            obstacle["type"] = o->getId();
            obstacle["position"]["x"] = o->getPosition().x;
            obstacle["position"]["y"] = o->getPosition().y;
            j["obstacles"].push_back(obstacle);
        }

        // Salvar estado dos inimigos
        for (int i = 0; i < movingEntities.getSize(); ++i)
        {
            auto e = movingEntities[i];
            if (e->getId() != ID::PLAYER1 && e->getId() != ID::PLAYER2)
            {
                if (e->getId() == ID::ENEMY && static_cast<Characters::Enemies::Enemy *>(e)->getHealth() > 0)
                {
                    json enemy;
                    enemy["type"] = e->getId();
                    enemy["position"]["x"] = e->getPosition().x;
                    enemy["position"]["y"] = e->getPosition().y;
                    enemy["health"] = static_cast<Characters::Enemies::Enemy *>(e)->getHealth();
                    j["enemies"].push_back(enemy);
                }
            }
        }

        // Salvar pontos dos jogadores
        j["player1Points"] = player1Points;
        j["player2Points"] = player2Points;

        // Abrir o arquivo para escrita, truncando o conteúdo existente
        std::ofstream file(filePath, std::ofstream::trunc);
        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo para salvar o estado do jogo: " << filePath << std::endl;
            return;
        }
        file << j.dump(4); // Escrever o JSON no arquivo com indentação de 4 espaços
        file.close();      // Fechar o arquivo após a escrita
    }

    void Level::clearState()
    {
        for (int i = 0; i < movingEntities.getSize(); ++i)
        {
            Entity *entity = movingEntities[i];
            if (entity)
            {
                delete entity; // Libere a memória alocada para a entidade
            }
        }
        movingEntities.cleanList(); // Limpar a lista de entidades em movimento

        // Limpar obstáculos
        for (int i = 0; i < obstacles.getSize(); ++i)
        {
            Entity *obstacle = obstacles[i];
            if (obstacle)
            {
                delete obstacle; // Libere a memória alocada para o obstáculo
            }
        }
        obstacles.cleanList(); // Limpar a lista de obstáculos

        // Resetar variáveis de estado do nível
        levelEnded = true;
        player1Points = 0;
        player2Points = 0;

        // Resetar referências aos jogadores
        Player1 = nullptr;
        Player2 = nullptr;
    }

    void Level::loadGameState(const std::string &filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
            return;
        }
        levelEnded = false;

        json j;
        file >> j;

        // Carregar estado dos jogadores
        if (j.contains("Player1") && j["Player1"].contains("position") && j["Player1"]["position"].contains("x") && j["Player1"]["position"].contains("y"))
        {
            auto p1 = j["Player1"];
            Player1 = static_cast<Characters::Player *>(Create(playerFactory, TupleF(p1["position"]["x"], p1["position"]["y"]), ID::PLAYER1));
            if (Player1)
            {
                if (p1.contains("health") && p1["health"].is_number_integer())
                {
                    Player1->set_health(p1["health"].get<int>());
                }
                if (p1.contains("points") && p1["points"].is_number_integer())
                {
                    Player1->setPoints(p1["points"].get<int>());
                }
                movingEntities.add(Player1);
            }
        }

        if (j.contains("Player2") && j["Player2"].contains("position") && j["Player2"]["position"].contains("x") && j["Player2"]["position"].contains("y"))
        {
            auto p2 = j["Player2"];
            Player2 = static_cast<Characters::Player *>(Create(playerFactory, TupleF(p2["position"]["x"], p2["position"]["y"]), ID::PLAYER2));
            if (Player2)
            {
                if (p2.contains("health") && p2["health"].is_number_integer())
                {
                    Player2->set_health(p2["health"].get<int>());
                }
                if (p2.contains("points") && p2["points"].is_number_integer())
                {
                    Player2->setPoints(p2["points"].get<int>());
                }
                movingEntities.add(Player2);
            }
        }

        // Carregar obstáculos
        if (j.contains("obstacles"))
        {
            for (const auto &o : j["obstacles"])
            {
                if (o.contains("position") && o["position"].contains("x") && o["position"].contains("y"))
                {
                    auto position = TupleF(o["position"]["x"], o["position"]["y"]);
                    auto type = o["type"].get<ID>();
                    auto obstacle = Create(oFactory, position, type);
                    if (obstacle)
                    {
                        obstacles.add(obstacle);
                    }
                }
            }
        }

        // Carregar inimigos
        if (j.contains("enemies"))
        {
            for (const auto &e : j["enemies"])
            {
                if (e.contains("position") && e["position"].contains("x") && e["position"].contains("y") && e.contains("health") && e["health"].is_number_integer())
                {
                    if (e["health"].get<int>() > 0)
                    {
                        auto position = TupleF(e["position"]["x"], e["position"]["y"]);
                        auto health = e["health"].get<int>();
                        auto type = e["type"].get<ID>();
                        auto enemy = Create(eFactory, position, type);
                        if (enemy)
                        {
                            movingEntities.add(enemy);
                        }
                    }
                }
            }
        }

        // Carregar pontos dos jogadores
        if (j.contains("player1Points") && j["player1Points"].is_number_integer())
        {
            player1Points = j["player1Points"].get<int>();
        }
        if (j.contains("player2Points") && j["player2Points"].is_number_integer())
        {
            player2Points = j["player2Points"].get<int>();
        }
    }

} // namespace States