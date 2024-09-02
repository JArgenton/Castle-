#include "States/Level.hpp"

#include "Entities/Obstacles/Plataform.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Characters/Enemies/EliteKnight.hpp"

#include "Entities/Weapons/Sword.hpp"
#include "Entities/Projectiles/Hook.hpp"
#include "Math/geometry.hpp"

#define BACKGROUND_LEVEL1 "assets/BackGrounds/OutSideCastle.png"

using namespace GraphicalElements;

namespace States
{
    Factories::ProjectilesFactory Level::projFactory;
    Factories::EnemiesFactory Level::eFactory;
    Factories::PlayerFactory Level::playerFactory;
    Factories::ObstaclesFactory Level::oFactory;

    List::EntityList Level::movingEntities;

    Characters::Player *Level::Player1;
    Characters::Player *Level::Player2;
    Control::PlayerControl Level::pControl;

    Level::Level(StateMachine *pSM, stateID _id) : State(pSM, _id),

                                                   background(),
                                                   obstacles(),
                                                   collisionManager(&obstacles, &Level::movingEntities),
                                                   pGraphicM(Managers::Graphics::get_instance()),
                                                   hpDisplay1(),
                                                   hpDisplay2(),
                                                   levelEnded(true),
                                                   player1Points(0),
                                                   player2Points(0)

    {
        pControl.setMachine(pStateMachine);
    }
    Level::~Level()
    {
    }
    bool Level::getEnded()
    {
        return levelEnded;
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

    void Level::executar()
    {
        collisionManager.check_collision();

        if (!Player1->isActive())
        {

            if (!Player2->getFullyCreated())
            {
                endLevel();
            }
            else if (!Player2->isActive())
            {

                endLevel();
            }
        }
    }

    void Level::update(const float dt)
    {

        float healthPercentage = static_cast<float>(Player1->getHealth()) / Player1->getTotalHealth();
        hpDisplay1.update(healthPercentage, TupleF(Player1->getPosition().x - 20, Player1->getPosition().y - 50));

        if (Player2->getFullyCreated() && Player2->isActive())
        {
            float healthPercentage2 = static_cast<float>(Player2->getHealth()) / Player2->getTotalHealth();
            hpDisplay2.update(healthPercentage2, TupleF(Player2->getPosition().x - 20, Player2->getPosition().y - 50));
        }

        TupleF centerpos = centerView();
        pGraphicM->centerViewOn(centerpos);

        background.render();
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

        executar();
    }

    void Level::render()
    {
        hpDisplay1.render();

        if (Player2 && Player2->isActive())
        {
            hpDisplay2.render();
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

    int Level::getPlayerPoints() const
    {
        if (Player1 && !Player2->getFullyCreated())
        {
            // out << Player1->getPoints() << endl;
            return Player1->getPoints();
        }
        else if (Player1 && Player2->getFullyCreated())
        {
            // uma fase com 2 em coop o score é a soma dos dois players
            return Player1->getPoints() + Player2->getPoints();
        }
        else
        {
            std::cerr << "Player1 é nulo!" << std::endl;
            return 0; // Retorna um valor padrão ou trate o erro
        }
    }

    void Level::saveGameState(const std::string &filePath)
    {
        json j;

        // Salvar estado dos jogadores
        j["GAME_STATE"] = pStateMachine->getLastStateID();

        if (Player1)
        {
            j["Player1"]["position"]["x"] = Player1->getPosition().x;
            j["Player1"]["position"]["y"] = Player1->getPosition().y;
            j["Player1"]["health"] = Player1->getHealth();
            j["Player1"]["points"] = Player1->getPoints();
            j["Player1"]["isActive"] = Player1->isActive();
            j["Player1"]["coolDownTimer"] = Player1->getCoolDownTimer();
            j["Player1"]["isAttacking"] = Player1->isAtking();
            j["Player1"]["TrapDuration"] = Player1->getTrapDuration();
        }

        if (Level::Player2)
        {
            j["Player2"]["position"]["x"] = Player2->getPosition().x;
            j["Player2"]["position"]["y"] = Player2->getPosition().y;
            j["Player2"]["health"] = Player2->getHealth();
            j["Player2"]["points"] = Player2->getPoints();
            j["Player2"]["isActive"] = Player2->isActive();
            j["Player2"]["fullyCreated"] = Player2->getFullyCreated();
            j["Player2"]["coolDownTimer"] = Player2->getCoolDownTimer();
            j["Player2"]["isAttacking"] = Player2->isAtking();
            j["Player2"]["TrapDuration"] = Player2->getTrapDuration();
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
                if (e->getId() == ID::ARCHER || e->getId() == ID::SOLDIER || e->getId() == ID::BOSS)
                {
                    json enemy;
                    enemy["type"] = e->getId();
                    enemy["position"]["x"] = e->getPosition().x;
                    enemy["position"]["y"] = e->getPosition().y;
                    enemy["health"] = static_cast<Characters::Enemies::Enemy *>(e)->getHealth();
                    enemy["coolDownTimer"] = static_cast<Characters::Enemies::Enemy *>(e)->getCoolDownTimer();
                    enemy["isAttacking"] = static_cast<Characters::Enemies::Enemy *>(e)->isAtking();
                    enemy["trapDuration"] = static_cast<Characters::Enemies::Enemy *>(e)->getTrapDuration();
                    enemy["trapTimer"] = static_cast<Characters::Enemies::Enemy *>(e)->getTrapTimmer();

                    if (e->getId() == ID::BOSS)
                    {
                        enemy["isHitting"] = static_cast<Characters::Enemies::EliteKnight *>(e)->getIsHitting();
                        enemy["hitTimmer"] = static_cast<Characters::Enemies::EliteKnight *>(e)->getHitTimmer();
                        enemy["hitLimit"] = static_cast<Characters::Enemies::EliteKnight *>(e)->getHitLimit();
                        enemy["grabTimmer"] = static_cast<Characters::Enemies::EliteKnight *>(e)->getGrabTimmer();
                        enemy["grabCooldown"] = static_cast<Characters::Enemies::EliteKnight *>(e)->getGrabCooldown();
                    }

                    j["enemies"].push_back(enemy);
                }
            }
        }

        // Salvar estado projeteis
        for (int i = 0; i < movingEntities.getSize(); ++i)
        {
            auto e = movingEntities[i];
            if (e->getId() == ID::ARROW || e->getId() == ID::HOOK)
            {
                json projectiles;
                projectiles["type"] = e->getId();
                projectiles["position"]["x"] = e->getPosition().x;
                projectiles["position"]["y"] = e->getPosition().y;
                switch (e->getId())
                {
                case ID::ARROW:
                    projectiles["direction"]["x"] = (static_cast<Entities::Projectiles::Arrow *>(e)->getDirectionX());
                    projectiles["direction"]["y"] = (static_cast<Entities::Projectiles::Arrow *>(e)->getDirectionY());
                    break;
                case ID::HOOK:
                    projectiles["direction"]["x"] = (static_cast<Entities::Projectiles::Hook *>(e)->getDirectionY());
                    projectiles["direction"]["y"] = (static_cast<Entities::Projectiles::Hook *>(e)->getDirectionX());
                    break;
                default:
                    break;
                }
                j["projectiles"].push_back(projectiles);
            }
        }

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
        pControl.reset();

        movingEntities.cleanList(); // Limpar a lista de entidades em movimento
        obstacles.cleanList();      // Limpar a lista de obstáculos

        levelEnded = false;
        player1Points = 0;
        player2Points = 0;

        // Resetar referências aos jogadores
        Player1 = nullptr;
        Player2 = nullptr;
    }

    void Level::loadEnemiesFromJson(const std::string &filePath, Characters::Player *pP1, Characters::Player *pP2)
    {
        if (pP1)
        {
            Player1 = pP1;
        }
        if (pP2)
        {
            Player2 = pP2;
        }
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
            return;
        }

        json j;
        file >> j;

        if (j.contains("enemies"))
        {
            for (const auto &enemyData : j["enemies"])
            {
                if (enemyData.contains("position") && enemyData["position"].contains("x") && enemyData["position"].contains("y"))
                {
                    TupleF position(enemyData["position"]["x"], enemyData["position"]["y"]);
                    ID enemyType = enemyData["type"].get<ID>();
                    auto enemy = Create(&eFactory, position, enemyType);
                    if (enemy)
                    {
                        if (enemyData.contains("health"))
                        {
                            static_cast<Characters::Enemies::Enemy *>(enemy)->set_health(enemyData["health"].get<int>());
                        }

                        static_cast<Characters::Enemies::Enemy *>(enemy)->setPlayer(Player1);
                        static_cast<Characters::Enemies::Enemy *>(enemy)->setPlayer(Player2);

                        if (enemyData.contains("coolDownTimer"))
                        {
                            static_cast<Characters::Enemies::Enemy *>(enemy)->set_coolDownTimer(enemyData["coolDownTimer"].get<float>());
                        }
                        if (enemyData.contains("isAttacking"))
                        {
                            static_cast<Characters::Enemies::Enemy *>(enemy)->set_isAtking(enemyData["isAttacking"].get<bool>());
                        }
                        if (enemyData.contains("trapDuration"))
                        {
                            static_cast<Characters::Enemies::Enemy *>(enemy)->isTraped(enemyData["trapDuration"].get<float>());
                        }
                        if (enemyType == ID::BOSS)
                        {
                            static_cast<Characters::Enemies::EliteKnight *>(enemy)->setPosition(TupleF(position));
                            if (enemyData.contains("isHitting"))
                            {
                                static_cast<Characters::Enemies::EliteKnight *>(enemy)->setIsHitting(enemyData["isHitting"].get<bool>());
                            }
                            if (enemyData.contains("grabTimmer"))
                            {
                                static_cast<Characters::Enemies::EliteKnight *>(enemy)->setGrabTimmer(enemyData["grabTimmer"].get<float>());
                            }
                            if (enemyData.contains("grabCooldown"))
                            {
                                static_cast<Characters::Enemies::EliteKnight *>(enemy)->setGrabCooldown(enemyData["grabCooldown"].get<float>());
                            }
                            if (enemyData.contains("hitTimmer"))
                            {
                                static_cast<Characters::Enemies::EliteKnight *>(enemy)->setHitTimmer(enemyData["hitTimmer"].get<float>());
                            }
                            if (enemyData.contains("hitLimit"))
                            {
                                static_cast<Characters::Enemies::EliteKnight *>(enemy)->setHitLimit(enemyData["hitLimit"].get<float>());
                            }
                        }

                        movingEntities.add(enemy);
                    }
                    else
                    {
                        std::cerr << "Falha ao criar inimigo do tipo " << enemyType << "." << std::endl;
                    }
                }
            }
        }
    }

    void Level::loadGameState(const std::string &filePath)
    {

        clearState();

        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
            return;
        }

        json j;
        file >> j;

        if (j.contains("GAME_STATE"))
        {
            int gameStateID = j["GAME_STATE"].get<int>(); // Obter o ID do estado do jogo
            pStateMachine->changeState(static_cast<States::stateID>(gameStateID));
        }

        // Carregar estado dos jogadores
        if (j.contains("Player1") && j["Player1"].contains("position") && j["Player1"]["position"].contains("x") && j["Player1"]["position"].contains("y"))
        {
            auto p1 = j["Player1"];
            Player1 = static_cast<Characters::Player *>(Create(&playerFactory, TupleF(p1["position"]["x"], p1["position"]["y"]), ID::PLAYER1));
            Player1->get_weapon();
            movingEntities.add(Player1->get_weapon());
            pControl.setPlayer(Player1);

            if (Player1)
            {
                if (p1.contains("health") && p1["health"].is_number_integer())
                {
                    Player1->set_health(p1["health"].get<int>());
                }
                if (p1.contains("isActive"))
                {
                    Player1->setActive(p1["isActive"].get<bool>());
                }
                if (p1.contains("coolDownTimer") && p1["coolDownTimer"].is_number_float())
                {
                    Player1->set_coolDownTimer(p1["coolDownTimer"].get<float>());
                }
                if (p1.contains("isAttacking"))
                {
                    Player1->set_isAtking(p1["isAttacking"].get<bool>());
                }
                if (p1.contains("points"))
                {
                    Player1->incrementPoints(p1["points"].get<int>());
                }
                if (p1.contains("trapTimmer") && p1["trapTimmer"].is_number_float())
                {
                }
                if (p1.contains("trapDuration") && p1["trapDuration"].is_number_float())
                {
                    Player1->isTraped(p1["trapDuration"].get<float>());
                }

                movingEntities.add(Player1);
            }
            else
            {
                std::cerr << "Falha ao criar Player1." << std::endl;
            }
        }

        if (j.contains("Player2") && j["Player2"].contains("position") && j["Player2"]["position"].contains("x") && j["Player2"]["position"].contains("y"))
        {
            auto p2 = j["Player2"];
            Player2 = static_cast<Characters::Player *>(Create(&playerFactory, TupleF(p2["position"]["x"], p2["position"]["y"]), ID::PLAYER2));
            Player2->get_weapon();
            movingEntities.add(Player2->get_weapon());
            if (Player2)
            {
                pControl.setPlayer(Player2);
                if (p2.contains("health") && p2["health"].is_number_integer())
                {
                    Player2->set_health(p2["health"].get<int>());
                }

                if (p2.contains("isActive"))
                {
                    Player2->setActive(p2["isActive"].get<bool>());
                }
                if (p2.contains("fullyCreated"))
                {
                    Player2->setFullyCreated(p2["fullyCreated"].get<bool>());
                    if (Player2->getFullyCreated())
                    {
                        Player2->initializeAfterLoad();
                    }
                }
                if (p2.contains("coolDownTimer") && p2["coolDownTimer"].is_number_float())
                {
                    Player2->set_coolDownTimer(p2["coolDownTimer"].get<float>());
                }
                if (p2.contains("isAttacking"))
                {
                    Player2->set_isAtking(p2["isAttacking"].get<bool>());
                }
                if (p2.contains("points"))
                {
                    Player2->incrementPoints(p2["points"].get<int>());
                }
                if (p2.contains("trapDuration") && p2["trapDuration"].is_number_float())
                {
                    Player2->isTraped(p2["trapDuration"].get<float>());
                }
                movingEntities.add(Player2);
            }
            else
            {
                std::cerr << "Falha ao criar Player2." << std::endl;
            }
        }
        else
        {
            std::cerr << "Dados de Player2 estão faltando ou são inválidos no arquivo JSON." << std::endl;
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
                    auto obstacle = Create(&oFactory, position, type);
                    if (obstacle)
                    {
                        obstacles.add(obstacle);
                    }
                    else
                    {
                        std::cerr << "Falha ao criar obstáculo do tipo " << type << "." << std::endl;
                    }
                }
            }
        }

        // Carregar Projeteis
        if (j.contains("projectiles"))
        {
            for (const auto &p : j["projectiles"])
            {

                if (p.contains("position") && p["position"].contains("x") && p["position"].contains("y"))
                {
                    try
                    {
                        auto position = Tuples::TupleF(p["position"]["x"], p["position"]["y"]);

                        // Ajuste a conversão de tipo conforme necessário
                        auto type = static_cast<Entities::ID>(p["type"].get<int>());

                        float x = p["direction"]["x"];
                        float y = p["direction"]["y"];
                        auto velocity = Tuples::TupleF(x, y);

                        createProjectile(position, type, velocity);
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << "Erro ao processar projétil: " << e.what() << std::endl;
                    }
                }
                else
                {
                    std::cerr << "Dados de posição incompletos para projétil." << std::endl;
                }
            }
        }

        // Carregar inimigos
        loadEnemiesFromJson("Saves/SAVEGAME.json", Player1, Player2);
    }

} // namespace States