#include "GraphElements/HealthBar.hpp"
#include "Managers/GraphicManager.hpp"

std::string texturePath = "assets/sp_bar_health_strip12.png";

namespace GraphicalElements
{

    HealthBar::HealthBar()
        : numStages(12)
    {
        texture = graphicManager->loadTexture(texturePath);

        stageWidth = texture->getSize().x / numStages;
        stageHeight = texture->getSize().y;

        body = new sf::RectangleShape(sf::Vector2f(stageWidth, stageHeight));

        initialize();
    }

    HealthBar::~HealthBar()
    {
        delete texture;
        delete body;
    }

    void HealthBar::update(float healthPercentage, TupleF position)
    {
        int stageIndex = static_cast<float>(healthPercentage * (numStages - 1));
        stageIndex = std::max(0, std::min(stageIndex, numStages - 1) - 1);

        body->setTexture(texture);
        body->setTextureRect(sf::IntRect(stageIndex * stageWidth, 0, stageWidth, stageHeight));
        body->setPosition(sf::Vector2f(position.x, position.y));
    }

    void HealthBar::render()
    {
        graphicManager->getWindow()->draw(*body);
    }
}