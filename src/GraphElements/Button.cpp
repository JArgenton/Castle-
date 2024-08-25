#include "GraphElements/Button.hpp"

#define BUTTON_PATH_DEFAULT "assets/Botoes/buttonStock1.png"
#define BUTTON_PATH_SELECTED "assets/Botoes/buttonStock3.png"
#define BUTTON_HEIGHT 80
#define BUTTON_WIDTH 300
#define BUTTON_TEXT_COLOR 77.6, 68.2, 44.3 // R, G, B
#define FONT_SIZE 30

namespace GraphicalElements
{

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