#include "Managers/GraphicManager.hpp"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAME_RATE_LIMIT 60
namespace Managers{

    Graphics* Graphics::instance = nullptr;

    Graphics::Graphics():
        window(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game")),        
        fontsMap(),
        texturesMap(),
        clock(),
        view(window->getDefaultView()),
        frameRateLimit(FRAME_RATE_LIMIT),
        dt(0)


    {
    window->setFramerateLimit(frameRateLimit);

    }
    Graphics* Graphics::get_instance(){
        if(instance == nullptr){
                instance = new Graphics();
        }

        return instance;
    }

    Graphics::~Graphics(){
        for(auto& MapElement : texturesMap){
            delete MapElement.second;
        }
        for(auto& MapElement : fontsMap){
            delete MapElement.second;
        }
        delete window;
    }

    sf::Font* Graphics::loadFont(const std::string& filepath){

        auto iterator = fontsMap.find(filepath);
        if(iterator != fontsMap.end()){
            return (iterator->second);
        }
        sf::Font* font = new sf::Font;
        if(!font->loadFromFile(filepath)){
            delete font;
            std::cout<<"ERROR LOADING FILE" << filepath<< std::endl;
            exit(1);
        }     
        fontsMap.insert(std::make_pair(filepath, font));
 
        return font;
    }

    sf::Texture* Graphics::loadTexture(const char* filepath){

        auto iterator = texturesMap.find(filepath);
        if(iterator != texturesMap.end()){
            return (iterator->second);
        }

        sf::Texture* texture = new sf::Texture;
        //verifica se o filepath corresponde a uma fonte, caso nao encontre-a, delete o obj e sai do programa (erro)
        if(!texture->loadFromFile(filepath)){
            delete texture;
            std::cout<<"ERROR LOADING FILE" << filepath<< std::endl;
            exit(1);
        }     

        texturesMap.insert(std::make_pair(filepath, texture));
        return texture;
    }

    void Graphics::centerViewOn(Coordinates::CoordF position){
        view.setCenter(sf::Vector2f(position.x, position.y));
        window->setView(view);
    }

    //funçoes para obter proporçoes da janela
    sf::Vector2u Graphics::getWindowSize() const { return window->getSize(); }
    sf::FloatRect Graphics::getViewBounds() { return view.getViewport(); }

    //funçoes para manipulaçao da janela
      bool Graphics::isWindowOpen() { return window->isOpen(); }

    void Graphics::clear(const sf::Color& color) { 
        if(isWindowOpen()){
            window->clear(color); 
            }
    }

    void Graphics::render(sf::RectangleShape *body) {
        window->draw(*body); 
    }
    void Graphics::render(sf::Text* text){
        window->draw(*text);
    }
    void Graphics::display() { 
        if(isWindowOpen()){
            window->display(); 
        }
    }

    void Graphics::closeWindow() {
        if (isWindowOpen()) {
            window->close();
        }
    }
bool Graphics::pullEvent(sf::Event& pEvent) {
        return window->pollEvent(pEvent);
    }

    void Graphics::updateDeltaTime(){
        //a funçao getElapsedTime() retorna o tempo que se passou desde a ultima vez que clock.restart() foi chamado
        this->dt = clock.getElapsedTime().asSeconds();
        clock.restart();
    }
}