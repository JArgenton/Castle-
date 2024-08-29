#include "Ent.hpp"
#include "Managers/GraphicManager.hpp"
Managers::Graphics *Ent::graphicManager(Managers::Graphics::get_instance());

Ent::Ent() : body()
{
    body = new sf::RectangleShape;
}

Ent::~Ent()
{
    if (body)
    {
        delete body;
    }
    body = nullptr;
}

void Ent::render()
{
    if (graphicManager)
    {
        graphicManager->render(body);
    }
}
void Ent::SetTexture(std::string &path)
{
    sf::Texture *ptext = graphicManager->loadTexture(path);
    body->setTexture(ptext);
}
void Ent::setOrigem(float width, float height)
{
    body->setOrigin(width / 2, height / 2);
}