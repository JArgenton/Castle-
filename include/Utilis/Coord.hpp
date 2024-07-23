#pragma once

#include <iostream>

using namespace std;

namespace Utilis{
namespace Coordinates{ 

template <typename TIPO>
class Coord{ 
public:
        TIPO x;
        TIPO y;
    Coord(TIPO x, TIPO y);
    Coord();
    ~Coord();

    // sobrecargas de operadores:

    // basicos ( =, +, -, *, / )

    void operator=(Coord<TIPO> coordenada);
    void operator+=(Coord<TIPO> coordenada);
    void operator-=(Coord<TIPO> coordenada);
    void operator*=(double escalar);
    void operator/=(double escalar);

    Coord<TIPO> operator+(Coord<TIPO> coordenada);
    Coord<TIPO> operator-(Coord<TIPO> coordenada);
    Coord<TIPO> operator*(Coord<TIPO> coordenada);
    Coord<TIPO> operator*(double escalar);
    Coord<TIPO> operator/(Coord<TIPO> coordenada);
    Coord<TIPO> operator/(double escalar);

};

typedef Coord<double> CoordD;
typedef Coord<float> CoordF;
typedef Coord<int> CoordI;
typedef Coord<unsigned int> CoordU;



template <typename TIPO>
    Coord<TIPO>::Coord(TIPO x, TIPO y):
        x(x),
        y(y) 
    {   }
template <typename TIPO>
Coord<TIPO>::Coord(){
    this->x = 0;
    this->y = 0;
}
template <typename TIPO>
Coord<TIPO>::~Coord(){
}
// Remove this
// Coord<float>::~Coord(){
// }
template <typename TIPO>
void Coord<TIPO>::operator=(Coord<TIPO> coordenada){
    this->x = coordenada.x;
    this->y = coordenada.y;
}

template <typename TIPO>
void Coord<TIPO>::operator+=(Coord<TIPO> coordenada){
    this->x += coordenada.x;
    this->y += coordenada.y;
}

template <typename TIPO>
void Coord<TIPO>::operator-=(Coord<TIPO> coordenada){
    this->x -= coordenada.x;
    this->y -= coordenada.y;
}

template <typename TIPO>
void Coord<TIPO>::operator*=(double escalar){
    this->x = this->x * escalar;
    this->y = this->y * escalar;
}

template <typename TIPO>
void Coord<TIPO>::operator/=(double escalar){
    if (escalar == 0.0f) {
        std::cout << "ERROR: Cannot divide by zero." << std::endl;
        exit(1);
    }
    this->x = this->x / escalar;
    this->y = this->y / escalar;
}
template <typename TIPO>
Coord<TIPO> Coord<TIPO>::operator+(Coord<TIPO> coordenada){
    return Coord<TIPO>(this->x + coordenada.x, this->y + coordenada.y);
}

template <typename TIPO>
Coord<TIPO> Coord<TIPO>::operator-(Coord<TIPO> coordenada){
    return Coord<TIPO>(this->x - coordenada.x, this->y - coordenada.y);
}

template <typename TIPO>
Coord<TIPO> Coord<TIPO>::operator*(Coord<TIPO> coordenada){
    return Coord<TIPO>(this->x * coordenada.x, this->y * coordenada.y);
}

template <typename TIPO>
Coord<TIPO> Coord<TIPO>::operator*(double escalar){
    return Coord<TIPO>(this->x * escalar, this->y * escalar);
}

template <typename TIPO>
Coord<TIPO> Coord<TIPO>::operator/(Coord<TIPO> coordenada){
    return Coord<TIPO>(this->x / coordenada.x, this->y / coordenada.y);
}

template <typename TIPO>
Coord<TIPO> Coord<TIPO>::operator/(double escalar){
    return Coord<TIPO>(this->x / escalar, this->y / escalar);
}





}
}