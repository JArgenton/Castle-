#pragma once
#include <iostream>
#include "Utilis/Coord.hpp"
#include "GraphicBodies/StaticBody.hpp"
#include "Weapons/Weapon.hpp"
using namespace std;
using namespace Utilis;

namespace Entities{

    #define GRAVITY 9.81f
    enum ID{
        empty = 0,
        PLAYER
    };
    class Entity{

     protected:
        ID id;
        GraphicBodies::StaticBody* image;

        
        /*general info*/
        Coordinates::CoordF size;
        Coordinates::CoordF position;

     public:
            Entity(Coordinates::CoordF psize = Coordinates::CoordF(0.0f, 0.0f),
            Coordinates::CoordF pposition = Coordinates::CoordF(0.0f, 0.0f), ID id = empty);

            ~Entity();

            /*SETs*/
            void set_position(Coordinates::CoordF pposition);
            void set_size(Coordinates::CoordF psize);

            /*GETs*/
            Coordinates::CoordF get_size();
            Coordinates::CoordF get_position();
            ID get_id();

            /*actions*/
            virtual void colide(Entity* other, Coordinates::CoordF intersec) = 0;

            /*visuals*/
            virtual void initialize() = 0; //carrega as texturas
            virtual void render() = 0; //atualiza posiçao da imagem

            /*Colisions*/
            virtual void moveOnColision(Entity* other) = 0; /*TODO classe Entity other*/
            
            /*update*/
            virtual void update(const float dt) = 0;
        

    };
}
