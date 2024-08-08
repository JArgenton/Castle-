#include "GraphicBodies/Body.hpp"


namespace GraphicBodies {

    Managers::Graphics* Body::graphicManager = Managers::Graphics::get_instance();
    /*Pegar instancia de gerenciador grafico*/
    Body::Body():
    selfbody()
    { 
        selfbody = new sf::RectangleShape();
    }

    Body::~Body() { }

    void Body::render() {
        graphicManager->render(selfbody);
    }

} // namespace GraphicalElements