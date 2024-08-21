#include <SFML/Graphics.hpp>
#include "Managers/GraphicManager.hpp"
using namespace std;

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
    void SetTexture(std::string &path);
    void setOrigem(float width, float height);
};
