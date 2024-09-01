#include "include/States/LevelOutterCastle.hpp"
#include "Entities/Obstacles/Plataform.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Weapons/Sword.hpp"
#include "Entities/Projectiles/Hook.hpp"
#define BACKGROUND_LEVEL1 "assets/BackGrounds/OutSideCastle.png"
namespace States
{
    OutterCastle::OutterCastle(StateMachine *pSM) : Level(pSM, stateID::LEVEL1),
                                                    maxEasyEnemies((rand() % 10) + 1)
    {
        background.initialize(BACKGROUND_LEVEL1, TupleF(pGraphicM->getWindowSize().x / 2.0f, pGraphicM->getWindowSize().y / 2), TupleF(pGraphicM->getWindowSize().x, pGraphicM->getWindowSize().y));
        background.render();
    }

    OutterCastle::~OutterCastle()
    {
    }

    void OutterCastle::executar()
    {
        background.update(centerView());

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
        if (movingEntities.getSize() <= 4)
        {
            endLevel();
        }
    }

    void OutterCastle::resetState()
    {
        if (levelEnded)
        {
            createFase("fase primeira final.tmj");
            levelEnded = false;
        }
    }

    void OutterCastle::endLevel()
    {
        if (!Player2->getFullyCreated())
        {
            Player2->setActive(false);
        }
        if (Player1->isActive() || Player2->isActive())
        {
            obstacles.cleanList();
            changeState(States::stateID::LEVEL2);
        }
        else
        {
            levelEnded = true;
            pControl.reset();
            movingEntities.cleanList();
            obstacles.cleanList();
            changeState(States::stateID::GAMEOVER);
        }
    }

    void OutterCastle::createFase(const std::string &path)
    {
        std::ifstream file(path);
        json tmjData;
        file >> tmjData;

        int bonusEnemyCounter = 0;

        // tamanho de cada bloco
        int tileWidth = tmjData["tilewidth"];
        int tileheight = tmjData["tileheight"];

        auto layer = tmjData["layers"][0];
        auto matrix = layer["data"];
        int width = layer["width"];
        int height = layer["height"];

        Entity *pE = nullptr;

        /*-------------------------------------CREATES AND INSERTS PLAYER INTO MOV.ENTITIES-------------------------------------*/
        Player1 = static_cast<Characters::Player *>(Create(&playerFactory, TupleF(250.0f, 1500.0f), ID::PLAYER1));
        if (Level::Player1)
        {
            movingEntities.add(Level::Player1);
            pControl.setPlayer(Level::Player1);
            movingEntities.add(dynamic_cast<Weapons::Sword *>(Level::Player1->get_weapon()));
        }
        Player2 = static_cast<Characters::Player *>(Create(&playerFactory, TupleF(250.0f, 1500.0f), ID::PLAYER2));

        if (Level::Player2)
        {
            movingEntities.add(Player2);
            pControl.setPlayer(Player2);
            movingEntities.add(dynamic_cast<Weapons::Sword *>(Level::Player2->get_weapon()));
        }

        /*---------------------------------LEVEL TERRAIN AND BASIC ENEMY CREATION---------------------------------*/
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
                    pE = Create(&Level::oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::PLATAFORM1);
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

                    pE = Create(&Level::eFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ARCHER);
                    if (pE)
                    {
                        movingEntities.add(pE);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Level::Player1);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Level::Player2);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }
                case 3:
                {
                    /*NO SOLDIERS IN THIS FASE*/
                    pE = Create(&Level::eFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::SOLDIER);
                    if (pE)
                    {
                        movingEntities.add(pE);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Level::Player1);
                        static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Level::Player2);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                    break;
                }
                case 4:
                {
                    if (bonusEnemyCounter++ < maxEasyEnemies)
                    {
                        pE = Create(&Level::eFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::empty);
                        if (pE)
                        {
                            movingEntities.add(pE);
                            static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Level::Player1);
                            static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Level::Player2);
                        }
                        else
                        {
                            cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                        }
                        break;
                    }
                }
                case 5:

                    break;

                case 6:
                {
                    pE = Create(&Level::oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::TRAP);
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
                    pE = Create(&Level::oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::TRAP);
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
                    /*HANDOM OBS, may be lava*/
                    pE = Create(&Level::oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::empty);
                    if (pE)
                    {
                        obstacles.add(pE);
                    }
                    else
                    {
                        cout << "nao foi possivel criar entidade, ponteiro nulo" << endl;
                    }
                }
                break;
                default:
                    break;
                }
            }
        }
        CreateEasyEnemy();
    }

    void OutterCastle::clearState()
    {
        pControl.reset();

        movingEntities.cleanList(); // Limpar a lista de entidades em movimento
        obstacles.cleanList();      // Limpar a lista de obstáculos

        levelEnded = false;
        player1Points = 0;
        player2Points = 0;
    }

    void OutterCastle::CreateEasyEnemy()
    {
        Entity *pE = nullptr;
        TupleF pos;
        if (rand() % 2)
        {
            pos(804.0f, 1508.0f);
        }
        else
        {
            pos(504.0f, 1008.0f);
        }
        for (int i = 0; i < 4; i++)
        {
            pE = Create(&eFactory, pos, SOLDIER);
            if (pE)
            {
                movingEntities.add(pE);

                static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Level::Player1);
                static_cast<Characters::Enemies::Enemy *>(pE)->setPlayer(Level::Player2);
                pos.x += 50.0f;
            }
        }
    }

}