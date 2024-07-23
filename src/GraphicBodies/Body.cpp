#include "GraphicBodies/Body.hpp"


namespace GraphicBodies {

    Managers::Graphics* Body::grapicManager = Managers::Graphics::get_instance();
    /*Pegar instancia de gerenciador grafico*/
    Body::Body() :
    shape()
    { }

    Body::~Body() { }

    void Body::render() {
        grapicManager->render(&shape);
    }

} // namespace GraphicalElements