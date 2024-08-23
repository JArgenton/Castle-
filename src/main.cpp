#include <iostream>
#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Weapons/Sword.hpp"
#include "Entities/Obstacles/Plataforma.hpp"
#include "Entities/Obstacles/Lava.hpp"
#include "Entities/Obstacles/Armadilha.hpp"
#include "Utilis/Tuple.hpp"
#include "Managers/ColisionManager.hpp"
#include "Entities/Characters/Enemies/Archer.hpp"

int main()
{
    // Obtém a instância do Graphics Manager
    Managers::Graphics *gpManager = Managers::Graphics::get_instance();
    Managers::Collision *ClManager = Managers::Collision::getInstance();
    Entities::Characters::Player p1;
    //  Loop principal
    TupleF pos = TupleF(110.0f, 110.0f);
    Entities::Weapons::Sword *pW = new Entities::Weapons::Sword;
    p1.set_weapon(pW);
    Entities::Obstacles::Plataforma plat1 = Entities::Obstacles::Plataforma(TupleF(200.0f, 200.0f));
    Entities::Obstacles::Plataforma plat2 = Entities::Obstacles::Plataforma(TupleF(400.0f, 200.0f));

    // Entities::Obstacles::Lava lava = Entities::Obstacles::Lava(TupleF(300.0f, 200.0f));
    Entities::Obstacles::Armadilha arm = Entities::Obstacles::Armadilha(TupleF(500.0f, 200.0f));
    int size = Entities::MovingEntity::MovingEntities.getSize();
    int sizes = Entities::StaticEntity::StaticEntities.getSize();

    printf("%d, %d \n", size, sizes);

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
            ClManager->check_collision();
            p1.update(4);
            plat1.render();
            plat2.render();
            // lava.render();
            arm.render();
            gpManager->updateDeltaTime();
            // Atualiza a janela
            p1.update(0.1);
            gpManager->display();
            gpManager->clear();
        }
    }

    std::cout << "Janela fechada" << std::endl;

    return 0;
}