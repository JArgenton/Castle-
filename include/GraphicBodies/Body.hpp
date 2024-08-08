#ifndef BODY_HPP
#define BODY_HPP

#include <SFML/Graphics.hpp>
#include "Managers/GraphicManager.hpp"
using namespace std;

namespace GraphicBodies{
    class Body
    {
    protected:
        sf::RectangleShape* selfbody;

        static Managers::Graphics* graphicManager;

     public:
        Body();
        ~Body();
        virtual void render();
    };
}
#endif