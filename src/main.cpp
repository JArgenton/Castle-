#include <iostream>
#include "Managers/GraphicManager.hpp"
#include "Entities/Characters/Player.hpp"

int main() {
    // Obtém a instância do Graphics Manager
    Managers::Graphics* gpManager = Managers::Graphics::get_instance();
    Entities::Characters::Player p1 = Entities::Characters::Player();
    p1.initialize();
    // Loop principal
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
        }

        // Lógica do jogo aqui

        // Limpa a janela com uma cor específica (preto neste caso)
        gpManager->clear(sf::Color::Black);

        // Desenha tudo que precisar na janela

        // Atualiza a janela
        gpManager->display();
    }

    std::cout << "Janela fechada" << std::endl;
    return 0;
}
