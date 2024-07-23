#include "GraphicBodies/StaticBody.hpp"

namespace GraphicBodies{
    StaticBody::StaticBody():
    texture(nullptr)
    { }
    StaticBody::~StaticBody(){ }

    void StaticBody::initialize(const char* path, Coordinates::CoordF position, Coordinates::CoordF size){
        texture = grapicManager->loadTexture(path);

        shape.setSize(sf::Vector2f(size.x, size.y));
        shape.setPosition(sf::Vector2f(position.x, position.y));
        shape.setOrigin(sf::Vector2f(size.x/2, size.y/2));
        shape.setTexture(texture);
    }
    void StaticBody::update(Coordinates::CoordF position){
        shape.setPosition(sf::Vector2f(position.x, position.y));
    }
}