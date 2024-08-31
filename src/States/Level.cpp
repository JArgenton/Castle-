#include "States/Level.hpp"

#include "Entities/Obstacles/Plataform.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Weapons/Sword.hpp"
#include "Entities/Projectiles/Hook.hpp"

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
    }
    void Level::update(const float dt)
    {
        if (id == stateID::LEVEL1)
        {
            if (!Player2->getFullyCreated())
            {
                background.update(TupleF(Player1->getPosition().x, Player1->getPosition().y));
            }
            else
            {
                background.update(TupleF((Player1->getPosition().x + Player2->getPosition().x) / 2, (Player1->getPosition().y + Player2->getPosition().y) / 2));
            }
        }

        float healthPercentage = static_cast<float>(Player1->getHealth()) / Player1->getTotalHealth();
        hpDisplay1.update(healthPercentage, TupleF(Player1->getPosition().x - 20, Player1->getPosition().y - 50));

        if (Player2->getFullyCreated() && Player2->isActive())
        {
            float healthPercentage2 = static_cast<float>(Player2->getHealth()) / Player2->getTotalHealth();
            hpDisplay2.update(healthPercentage2, TupleF(Player2->getPosition().x - 20, Player2->getPosition().y - 50));
        }

        // cout << Player1->getHealth() << endl;
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
        /* oque esta aqui estava depois das updates*/
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
        if (Level::Player1)
        {
            return Level::Player1->getPoints();
        }
        else
        {
            std::cerr << "Player1 é nulo!" << std::endl;
            return 0; // Retorna um valor padrão ou trate o erro
        }
    }

    /*void Level::saveGameState(const std::string &filePath)
    {
        json j;

        // Salvar estado dos jogadores
        if (Level::Player1)
        {
            j["Player1"]["position"]["x"] = Level::Player1->getPosition().x;
            j["Player1"]["position"]["y"] = Level::Player1->getPosition().y;
            j["Player1"]["health"] = Level::Player1->getHealth();
            j["Player1"]["points"] = Level::Player1->getPoints();
            j["Player1"]["isActive"] = Level::Player1->isActive();
        }

        if (Level::Player2)
        {
            j["Player2"]["position"]["x"] = Level::Player2->getPosition().x;
            j["Player2"]["position"]["y"] = Level::Player2->getPosition().y;
            j["Player2"]["health"] = Level::Player2->getHealth();
            j["Player2"]["points"] = Level::Player2->getPoints();
            j["Player2"]["isActive"] = Level::Player2->isActive();
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
                    enemy["targetedPlayer"] = static_cast<Characters::Enemies::Enemy *>(e)->getTargetPlayerId();

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
*/
}