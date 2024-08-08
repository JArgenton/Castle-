#include "GraphicBodies/StaticBody.hpp"

namespace GraphicBodies{
    StaticBody::StaticBody():
    Body()
    {     }
    StaticBody::~StaticBody(){ }

    void StaticBody::initialize(const char* path, Coordinates::CoordF position, Coordinates::CoordF size){
        sf::Texture * ptext = graphicManager->loadTexture(path);
        
        selfbody->setSize(sf::Vector2f(size.x, size.y));
        selfbody->setPosition(sf::Vector2f(position.x, position.y));
        selfbody->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
        selfbody->setTexture(ptext);
    }
    void StaticBody::update(Coordinates::CoordF position){
        selfbody->setPosition(sf::Vector2f(position.x, position.y));
    }
}