#include "Principal.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"

Factories::ProjectilesFactory Principal::projFactory;
List::EntityList Principal::MovingEntities;

Principal::Principal() : eFactory(),
                         playerFactory(),
                         oFactory(),
                         Player1(),
                         Player2(),
                         ClManager(&StaticEntities, &Principal::MovingEntities),
                         gpManager(Managers::Graphics::get_instance())
{
    eFactory = new Factories::EnemiesFactory;
    playerFactory = new Factories::PlayerFactory;
    oFactory = new Factories::ObstaclesFactory;
}

Principal::~Principal()
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
    MovingEntities.cleanList();
    StaticEntities.cleanList();
}

void Principal::exec()
{
    createFase("map.tmj");
    float dt = 0;

    while (gpManager->isWindowOpen())
    {
        sf::Event event;
        // Processa eventos
        gpManager->updateDeltaTime();
        dt = gpManager->getDeltaTime();

        while (gpManager->pullEvent(event))
        {
            // Verifica o tipo de evento

            if (event.type == sf::Event::Closed)
            {
                gpManager->closeWindow();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    gpManager->closeWindow();
                }
            }
        }
        for (int i = 0; i < StaticEntities.getSize(); i++)
        {
            StaticEntities[i]->render();
        }

        for (int i = 0; i < MovingEntities.getSize(); i++)
        {

            static_cast<MovingEntity *>(MovingEntities[i])->update(dt);
            if (!static_cast<MovingEntity *>(MovingEntities[i])->isActive())
            {
                MovingEntities.deleteEntity(i);
            }
        }

        ClManager.check_collision();

        // Atualiza a janela
        gpManager->display();
        gpManager->clear();
    }

    std::cout << "Janela fechada" << std::endl;
}

void Principal::createFase(const std::string &path)
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

    Player1 = static_cast<Characters::Player *>(Create(playerFactory, TupleF(300.0f, 270.0f), ID::PLAYER1));
    if (Player1)
    {
        MovingEntities.add(Player1);
    }
    Entity *pE = Create(eFactory, TupleF(350.0f, 260.0f), ARCHER);
    if (pE)
    {
        MovingEntities.add(pE);
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
                StaticEntities.add(Create(oFactory, TupleF((100.0f + x * tileWidth), (100.0f + y * tileheight)), ID::PLATAFORMA));
            }
        }
    }
}

Entity *Principal::Create(Factories::EntityFactory *pFactory, TupleF _position, ID _id)
{
    return pFactory->FactoryMethood(_position, _id);
}
void Principal::createProjectile(TupleF _position, ID _id)
{
    Entity *pE = Create(&projFactory, _position, _id);

    if (pE)
    {

        MovingEntities.add(pE);
    }
}
