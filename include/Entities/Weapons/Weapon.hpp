#pragma once
#include <iostream>
#include "Entities/MovingEntity.hpp"
using namespace std;

namespace Entities
{
    namespace Characters
    {
        class Player; // Declaração de classe avançada
    }
    namespace Weapons
    {
        class Weapon : public Entities::MovingEntity
        {
        protected:
            /*Cooldowns (const)*/
            Characters::Player *owner;
            Coordinates::CoordF ownerPosition;

        public:
            Weapon();
            virtual ~Weapon();
            virtual void atack() = 0;
            void setPlayer(Characters::Player *pP);
            virtual void WeaponInitialize(Characters::Player *pP) = 0;
            virtual void setPosition() = 0;
            void colide(Entity *other, Coordinates::CoordF intersec) override {}
            void moveOnColision(Entity *other) override {}
            virtual void update(const float dt) = 0;
            virtual void render() = 0;
        };
    }
}