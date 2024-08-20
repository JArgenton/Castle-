#include <iostream>
#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"
#include "Entities/Weapons/Sword.hpp"
#include "Entities/Obstacles/Plataforma.hpp"
#include "Utilis/Tuple.hpp"

int main()
{
    // Obtém a instância do Graphics Manager
    Managers::Graphics *gpManager = Managers::Graphics::get_instance();
    Entities::Characters::Player p1;
    //  Loop principal
    TupleF pos = TupleF(110.0f, 110.0f);
    Entities::Weapons::Sword *pW = new Entities::Weapons::Sword;
    p1.set_weapon(pW);
    Entities::Obstacles::Plataforma plat = Entities::Obstacles::Plataforma(TupleF(200.0f, 200.0f));

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
            p1.update(4);
            plat.render();
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