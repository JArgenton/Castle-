#include "include/States/LevelInnerClastle.hpp"
#include "Entities/Obstacles/Plataform.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Entities/Weapons/Sword.hpp"
#include "Entities/Projectiles/Hook.hpp"
#define BACKGROUND_LEVEL2 "assets/BackGrounds/leaderBG.jpeg"
namespace States
{
    InnerCastle::InnerCastle(StateMachine *pSM) : Level(pSM, stateID::LEVEL2),
                                                  maxArchers((rand() % 5) + 1)
    {
        background.initialize(BACKGROUND_LEVEL2, TupleF(pGraphicM->getWindowSize().x / 2.0f, pGraphicM->getWindowSize().y / 2), TupleF(pGraphicM->getWindowSize().x, pGraphicM->getWindowSize().y));
        background.render();
        levelEnded = true;
    }

    InnerCastle::~InnerCastle()
    {
        movingEntities.cleanList();
        Player1 = nullptr;
        Player2 = nullptr;
    }

    void InnerCastle::resetState()
    {
        pGraphicM->clear();
        if (levelEnded)
        {
            createFase("fase 2.tmj");
            levelEnded = false;
        }
    }
    void InnerCastle::executar()
    {
        background.update(centerView());
        collisionManager.check_collision();

        cout << movingEntities.getSize() << endl;
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
            else if (movingEntities.getSize() <= 4)
            {
                endLevel();
            }
        }
    }

    void InnerCastle::endLevel()
    {
        obstacles.cleanList();
        changeState(States::stateID::GAMEOVER);
    }

    void InnerCastle::createFase(const std::string &path)
    {
        cout << "HAha i criateHA" << endl;

        std::ifstream file(path);
        json tmjData;
        file >> tmjData;

        int bonusArcherCounter = 0;

        // tamanho de cada bloco
        int tileWidth = tmjData["tilewidth"];
        int tileheight = tmjData["tileheight"];

        auto layer = tmjData["layers"][0];
        auto matrix = layer["data"];
        int width = layer["width"];
        int height = layer["height"];

        Entity *pE = nullptr;

        /*-------------------------------------CREATES AND INSERTS PLAYER INTO MOV.ENTITIES-------------------------------------*/
        // Player1 = static_cast<Characters::Player *>(Create(&playerFactory, TupleF(250.0f, 1500.0f), ID::PLAYER1));
        if (Level::Player1)
        {
            Player1->setPosition(TupleF(1302.0f, 200.0f));
            pControl.setPlayer(Level::Player1);
        }
        // Player2 = static_cast<Characters::Player *>(Create(&playerFactory, TupleF(250.0f, 1500.0f), ID::PLAYER2));

        if (Level::Player2)
        {
            Player2->setPosition(TupleF(1302.0f, 200.0f));
            pControl.setPlayer(Player2);
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
                }
                case 4:
                {
                    if (bonusArcherCounter++ < maxArchers)
                    {
                        pE = Create(&Level::eFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::ARCHER);
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
                    /* NO TRAPS IN THIS FASE*/
                }
                case 7:
                {
                    pE = Create(&Level::oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::empty);
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
                    /* NO Random obstacles IN THIS FASE*/
                }
                break;

                case 9:
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
                default:
                    break;
                }
            }
        }

        CreateHardEnemy();
    }

    void InnerCastle::clearState()
    {
        pControl.reset();

        movingEntities.cleanList(); // Limpar a lista de entidades em movimento
        obstacles.cleanList();      // Limpar a lista de obstáculos

        levelEnded = false;
        player1Points = 0;
        player2Points = 0;
        boss = nullptr;
    }

    void InnerCastle::CreateHardEnemy()
    {
        TupleF pos;
        if (rand() % 2)
        {
            pos(1302.0f, 1000.0f);
        }
        else
        {
            pos(1302.0f, 1000.0f);
        }
        boss = static_cast<Characters::Enemies::BigBoss *>(Create(&Level::eFactory, pos, ID::BOSS));

        if (boss)
        {
            movingEntities.add(boss);

            static_cast<Characters::Enemies::Enemy *>(boss)->setPlayer(Level::Player1);
            static_cast<Characters::Enemies::Enemy *>(boss)->setPlayer(Level::Player2);
        }
    }
}