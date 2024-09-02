#include "GraphElements/Button.hpp"

#define BUTTON_PATH_DEFAULT "assets/Botoes/buttonStock1.png"
#define BUTTON_PATH_SELECTED "assets/Botoes/buttonStock1h.png"
#define BUTTON_HEIGHT 180
#define BUTTON_WIDTH 350
#define BUTTON_TEXT_COLOR 177.6, 168.2, 144.3 // R, G, B
#define FONT_SIZE 20

namespace GraphicalElements
{
    /*CLASSE BASEADA NA IMPLEMENTAÇAO DO MONITOR BURDA*/

    Button::Button(TupleF position, std::string info) : textInfo(position, info),
                                                        defaultTexture(nullptr),
                                                        selectedTexture(nullptr)
    {
        defaultTexture = graphicManager->loadTexture(BUTTON_PATH_DEFAULT);
        selectedTexture = graphicManager->loadTexture(BUTTON_PATH_SELECTED);

        body->setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));

        body->setOrigin(sf::Vector2f(BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2));

        body->setPosition(sf::Vector2f(position.x, position.y));

        body->setTexture(defaultTexture);

        textInfo.setFontSize(FONT_SIZE);

        textInfo.setTextAlignment(TextAlignment::center);

        textInfo.setTextColor(BUTTON_TEXT_COLOR);

        textInfo.setPosition(TupleF(position.x, position.y));
    }

    Button::~Button() {}

    void Button::select(const bool isSelected)
    {
        if (isSelected)
            body->setTexture(selectedTexture);
        else
            body->setTexture(defaultTexture);
    }

    void Button::render()
    {
        graphicManager->render(body);

        textInfo.render();
    }

} // namespace GraphicalElements