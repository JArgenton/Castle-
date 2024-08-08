#pragma once 
#include "Utilis/Coord.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map> // gerenciar texturas
using namespace Utilis;

namespace Managers{

    class Graphics
    {
    private:
        sf::RenderWindow *window; // janela que o jogo passara

        std::unordered_map<std::string, sf::Font*> fontsMap; // Mapa de fontes (ED2), carregar e organizar fontes de maneira eficiente
        std::unordered_map<const char*, sf::Texture*> texturesMap; // Mapa de texturas (ED2), carregar, organizar as texturas utilizadas

        // clock para processamento
        sf::Clock clock; 

        //camera do jogo (sera centralizada no jogador)
        sf::View view;

        //serie de variaveis para controle de fps
        unsigned int frameRateLimit;

        float dt;

    static Managers::Graphics* instance;

    Graphics();

    public:
        // a destrutora continua publica
        ~Graphics();

        //funçoes distinadas a carregar e manipular fontes
        sf::Font*  loadFont(const std::string& filepath);

        //funçoes destinadas a carregar e manipular texturas
        sf::Texture* loadTexture(const char* filepath);

        //funçoes destinadas a carregar e centralizar a tela.
        void centerViewOn(Coordinates::CoordF position);

        //funçoes para obter proporçoes da janela
        sf::Vector2u getWindowSize() const;

        /*a funçao retorna um timpo "FloatRect", tal estrutura é um retangulo com coordenadas com ponto flutuante que representam os limites 
        da view atual com relaçao a janela. Essa funçao tera uso para o gerenciador de colisoes. */
        sf::FloatRect getViewBounds();

        //funçoes para manipulaçao da janela
        bool isWindowOpen();
        //limpa a janela com a cor padrao (preto)
        void clear(const sf::Color& color = sf::Color::Black);

        //a funçao render adiciona os obj a serem desenhados em uma fila, que seja executada quando a tela atualizar
        void render(sf::RectangleShape *body);
        void render(sf::Text* text);

        //a funçao display é chamada apos desenhar os obj(render), e serve para exibir tais obj (exibe alteraçoes)
        void display();
        void closeWindow();

        //funçao para atualizar o tempo, inspirada do tutorial jogo SFML do Monitor Burda
        void updateDeltaTime();

        /*events*/
        bool pullEvent(sf::Event& pEvent);

    Graphics(const Graphics&) = delete;

    Graphics& operator=(const Graphics&) = delete;

    static Graphics* get_instance();
    };
}