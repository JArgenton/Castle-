#include <iostream>
#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"

int main() {
    // Obtém a instância do Graphics Manager
    Managers::Graphics* gpManager = Managers::Graphics::get_instance();
    Entities::Characters::Player p1 = Entities::Characters::Player();
    // Loop principal
        Utilis::Coordinates::CoordF* pos;
        pos = new Utilis::Coordinates::CoordF(110.0f, 110.0f);
        p1.set_position(*pos);
        
        delete pos;
    while (gpManager->isWindowOpen()) {
        sf::Event event;
        // Processa eventos


        while (gpManager->pullEvent(event)) {
            // Verifica o tipo de evento

            if (event.type == sf::Event::Closed) {
                gpManager->closeWindow();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    gpManager->closeWindow();
                }
            }
        p1.update(4);
        gpManager->updateDeltaTime();
        // Atualiza a janela
        gpManager->display();
        gpManager->clear();

           
        }

    }

    std::cout << "Janela fechada" << std::endl;
    return 0;
}
