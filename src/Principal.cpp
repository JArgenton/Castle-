#include "Principal.hpp"

Factories::ProjectilesFactory Principal::projFactory;
List::EntityList Principal::MovingEntities;

Principal::Principal() : eFactory(),
                         playerFactory(),
                         oFactory(),
                         ClManager(&StaticEntities, &Principal::MovingEntities),
                         gpManager(Managers::Graphics::get_instance())
{
    eFactory = new Factories::EnemiesFactory;
    playerFactory = new Factories::PlayerFactory;
    oFactory = new Factories::ObstaclesFactory;
}

Principal::~Principal()
{
    delete eFactory;
    delete playerFactory;
    delete oFactory;
    delete Player1;
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
        }

        ClManager.check_collision();

        // Atualiza a janela
        gpManager->display();
        gpManager->clear();
    }

    std::cout << "Janela fechada" << std::endl;
}

Entity *Principal::Create(Factories::EntityFactory *pFactory, TupleF _position, ID _id)
{
    return pFactory->FactoryMethood(_position, _id);
}

void Principal::createFase(const std::string &path)
{

    Player1 = static_cast<Characters::Player *>(Create(playerFactory, TupleF(160.0f, 160.0f), ID::PLAYER1));
    if (Player1)
    {
        MovingEntities.add(Player1);
    }
    Entity *pE = Create(eFactory, TupleF(200.0f, 160.0f), ARCHER);
    if (pE)
    {
        MovingEntities.add(pE);
    }

    // Cria um objeto ifstream para ler o arquivo
    std::ifstream file(path);

    // Cria um objeto json
    json tmjData;

    // Lê o arquivo json para o objeto json
    file >> tmjData;

    // tamanho de cada bloco
    int tileWidth = tmjData["tilewidth"];
    int tileheight = tmjData["tileheight"];

    auto layer = tmjData["layers"][0];
    auto matrix = layer["data"];
    int width = layer["width"];
    int height = layer["height"];

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
void Principal::createProjectile(TupleF _position, ID _id)
{
    Entity *pE = Create(&projFactory, _position, _id);
    if (pE)
    {
        MovingEntities.add(pE);
    }
}
