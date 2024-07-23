#include <SFML/Graphics.hpp>
#include <iostream>
#include "Managers/GraphicManager.hpp"
using namespace std;

namespace GraphicBodies{
    class Body
    {
    protected:
        sf::RectangleShape shape;

        static Managers::Graphics* grapicManager;

     public:
        Body();
        ~Body();
        virtual void render();
    };
}