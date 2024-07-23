#include "Body.hpp"
#include "Utilis/Coord.hpp"
using namespace Utilis;

namespace GraphicBodies{

    class StaticBody : public Body{

     private:
        sf::Texture* texture;

     public:
     StaticBody();
     ~StaticBody();

     void initialize(const char* path, Coordinates::CoordF position, Coordinates::CoordF size);
     void update(Coordinates::CoordF position);
    };

}