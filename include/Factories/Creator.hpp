#include "Factories/EnemiesFactory.hpp"
#include "Factories/ObstaclesFactory.hpp"
#include "Factories/PlayerFactory.hpp"
#include "Managers/ColisionManager.hpp"
#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"

#include "Utilis/EntityList.hpp"

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
                             ClManager(&StaticEntities, &MovingEntities),
                             gpManager(Managers::Graphics::get_instance())
    {
        eFactory = new EnemiesFactory;
        pFactory = new PlayerFactory;
        oFactory = new ObstaclesFactory;

        this->exec();
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
                for (int i = 0; i <= 9; i++)
                {

                    StaticEntities[i]->render();
                }
                ClManager.check_collision();
                Player1->update(0.5);

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
        cout << "dsdsdfs" << endl;

        TupleF position = TupleF(100.0f, 100.0f);
        Player1 = static_cast<Characters::Player *>(Create(pFactory, position, ID::PLAYER1));
        MovingEntities.add(Player1);
        Entities::Entity *pE = nullptr;
        position = TupleF(0.0f, 200.0f);
        cout << "xececa" << endl;
        for (int i = 0; i <= 9; i++)
        {

            position += (TupleF(50.0f, 0.0f));

            pE = Create((EntityFactory *)oFactory, position, ID::PLATAFORMA);
            if (pE)
            {
                cout << i << endl;
                StaticEntities.add(pE);
                cout << StaticEntities[i]->getPosition().x << endl;
            }
        }
        position += (TupleF(100.0f, 100.0f));
        StaticEntities.add(Create((EntityFactory *)oFactory, position, ID::PLATAFORMA));
    }

} // namespace Factory
