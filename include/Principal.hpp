#pragma once

#include "Factories/EnemiesFactory.hpp"
#include "Factories/ObstaclesFactory.hpp"
#include "Factories/PlayerFactory.hpp"
#include "Managers/ColisionManager.hpp"
#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Characters/Enemies/Enemy.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"
#include "Utilis/EntityList.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace Factories
{
    class Principal
    {
    private:
        Factories::EnemiesFactory *eFactory;
        Factories::PlayerFactory *pFactory;
        Factories::ObstaclesFactory *oFactory;

        static List::EntityList MovingEntities;
        static List::EntityList StaticEntities;

        Characters::Player *Player1;
        Characters::Player *Player2;

        Characters::Enemies::Archer *Arc;

        Managers::Collision ClManager;
        Managers::Graphics *gpManager;

    public:
        Principal();
        ~Principal();
        void exec();
        void createFase();
        Entity *Create(EntityFactory *pFactory, TupleF _position, ID _id = empty);
    };
    List::EntityList Principal::MovingEntities;
    List::EntityList Principal::StaticEntities;

    Principal::Principal() : eFactory(),
                             pFactory(),
                             oFactory(),
                             Player1(),
                             Player2(),
                             Arc(),
                             ClManager(&StaticEntities, &MovingEntities),
                             gpManager(Managers::Graphics::get_instance())
    {
        eFactory = new EnemiesFactory;
        pFactory = new PlayerFactory;
        oFactory = new ObstaclesFactory;
    }

    Principal::~Principal()
    {
        delete eFactory;
        delete pFactory;
        delete oFactory;
        delete Player1;
        if (Player2)
        {
            delete Player2;
            Player2 = nullptr;
        }
        eFactory = nullptr;
        pFactory = nullptr;
        oFactory = nullptr;
        Player1 = nullptr;
        MovingEntities.cleanList();
        StaticEntities.cleanList();
    }
    void Principal::exec()
    {
        createFase();
        while (gpManager->isWindowOpen())
        {
            sf::Event event;
            // Processa eventos

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

                for (int i = 0; i < StaticEntities.getSize(); i++)
                {
                    StaticEntities[i]->render();
                }
                ClManager.check_collision();
                Player1->update(0.5);
                // Arc->update(0.5);

                gpManager->updateDeltaTime();
                // Atualiza a janela
                gpManager->display();
                gpManager->clear();
            }
        }

        std::cout << "Janela fechada" << std::endl;
    }

    Entity *Principal::Create(EntityFactory *pFactory, TupleF _position, ID _id)
    {
        return pFactory->FactoryMethood(_position, _id);
    }

    void Principal::createFase(/*.JSON*/)
    {

        // Cria um objeto ifstream para ler o arquivo
        std::ifstream i("map.tmj");

        // Cria um objeto json
        json j;

        // Lê o arquivo json para o objeto json
        i >> j;

        // Agora você pode acessar os valores no json como se fossem membros de um objeto
        std::vector<int> layerData = j["layers"][0]["data"];
        int width = j["layers"][0]["width"];
        int height = j["layers"][0]["height"];

        TupleF pos = TupleF(100.0f, 100.0f);
        // Itera sobre os dados da camada
        Entity *pE = nullptr;
        for (int y = 0; y < height; ++y)
        {
            pos.y += 100;
            for (int x = 0; x < width; ++x)
            {
                pos.x += 10;
                int value = layerData[y * width + x];
                // Se o valor for 1 ou 2, cria uma plataforma
                if (value == 1 || value == 2)
                {
                    pE = Create(oFactory, pos, ID::PLATAFORMA);
                    if (pE)
                    {

                        StaticEntities.add(pE);
                    }
                }
            }
        }
        Player1 = static_cast<Characters::Player *>(Create(pFactory, TupleF(200.0f, 200.0f), ID::PLAYER1));
        if (Player1)
        {
            MovingEntities.add(Player1);
        }

        Arc = static_cast<Characters::Enemies::Archer *>(Create(pFactory, TupleF(400.0f, 200.0f), ID::ARCHER));
        if (Arc)
        {
            MovingEntities.add(Arc);
        }
        printf("%d", StaticEntities.getSize());
    }
} // namespace Factory
