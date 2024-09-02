#include "GraphElements/StaticAnimation.hpp"

#include "Managers/GraphicManager.hpp"

namespace GraphicalElements
{
    /*CLASSE BASEADA NA IMPLEMENTAÇAO DO MONITOR BURDA*/

    StaticAnimation::StaticAnimation() : texture(nullptr) {}

    StaticAnimation::~StaticAnimation() {}

    void StaticAnimation::initialize(const char *path, TupleF position, TupleF size)
    {
        texture = graphicManager->loadTexture(path);

        body->setSize(sf::Vector2f(size.x, size.y));
        body->setPosition(sf::Vector2f(position.x, position.y));
        body->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
        body->setTexture(texture);
    }

    void StaticAnimation::update(TupleF position)
    {
        body->setPosition(sf::Vector2f(position.x, position.y));
    }

} // namespace GraphicalElements