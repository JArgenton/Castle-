#ifndef STATIC_BODY_HPP
#define STATIC_BODY_HPP

#include "Body.hpp"
#include "Utilis/Coord.hpp"
#include <SFML/Graphics.hpp>
using namespace Utilis;

namespace GraphicBodies{

    class StaticBody : public Body{

     private:
     
     public:
     StaticBody();
     ~StaticBody();

     void initialize(const char* path, Coordinates::CoordF position, Coordinates::CoordF size);
     void update(Coordinates::CoordF position);
    };

}
#endif // STATIC_BODY_HPP