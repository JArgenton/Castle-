#include "Managers/GraphicManager.hpp"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define FRAME_RATE_LIMIT 60
namespace Managers
{

    Graphics *Graphics::instance = nullptr;

    Graphics::Graphics() : window(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game")),
                           textureFactory(),
                           fontFactory(),
                           clock(),
                           view(window->getDefaultView()),
                           frameRateLimit(FRAME_RATE_LIMIT),
                           dt(0)

    {
        window->setFramerateLimit(frameRateLimit);
    }
    Graphics *Graphics::get_instance()
    {
        if (instance == nullptr)
        {
            instance = new Graphics();
        }

        return instance;
    }

    Graphics::~Graphics()
    {
        delete window;
        instance = nullptr;
    }

    sf::Font *Graphics::loadFont(const std::string &filepath)
    {
        return fontFactory.getResource(filepath);
    }

    sf::Texture *Graphics::loadTexture(const std::string &filepath)
    {
        return textureFactory.getResource(filepath);
    }

    void Graphics::centerViewOn(TupleF position)
    {
        view.setCenter(sf::Vector2f(position.x, position.y));
        window->setView(view);
    }

    // funçoes para obter proporçoes da janela
    sf::Vector2u Graphics::getWindowSize() const { return window->getSize(); }
    sf::FloatRect Graphics::getViewBounds() { return view.getViewport(); }

    // funçoes para manipulaçao da janela
    bool Graphics::isWindowOpen() { return window->isOpen(); }

    void Graphics::clear(const sf::Color &color)
    {
        if (isWindowOpen())
        {
            window->clear(color);
        }
    }

    void Graphics::render(sf::RectangleShape *body)
    {
        window->draw(*body);
    }
    void Graphics::render(sf::Text *text)
    {
        window->draw(*text);
    }
    void Graphics::display()
    {
        if (isWindowOpen())
        {
            window->display();
        }
    }

    void Graphics::closeWindow()
    {
        if (isWindowOpen())
        {
            window->close();
        }
    }
    bool Graphics::pullEvent(sf::Event &pEvent)
    {
        return window->pollEvent(pEvent);
    }

    void Graphics::updateDeltaTime()
    {
        // a funçao getElapsedTime() retorna o tempo que se passou desde a ultima vez que clock.restart() foi chamado
        this->dt = clock.getElapsedTime().asSeconds();
        clock.restart();
    }

    sf::RenderWindow *Graphics::getWindow() const
    {
        return window;
    }
}