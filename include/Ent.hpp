#pragma once
#include "Utilis/Tuple.hpp"
#include <SFML/Graphics.hpp>

using namespace Tuples;

using namespace std;
namespace Managers
{
    class Graphics;
}
class Ent
{
protected:
    static Managers::Graphics *graphicManager;
    sf::RectangleShape *body;

public:
    Ent();
    virtual ~Ent();
    virtual void render();
    virtual void initialize() = 0;
    virtual void execute() = 0;
    void SetTexture(string &path);
    void setOrigem(float width, float height);
};
