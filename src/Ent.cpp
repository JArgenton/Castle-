#include "Ent.hpp"
Managers::Graphics *Ent::graphicManager(Managers::Graphics::get_instance());

Ent::Ent() : body()
{
}

Ent::~Ent()
{

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
    body->setOrigin(width, height);
}
