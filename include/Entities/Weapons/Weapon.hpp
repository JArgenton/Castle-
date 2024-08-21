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

        public:
            Weapon();
            virtual ~Weapon();
            virtual void atack() = 0;
            void setPlayer(Characters::Player *pP);
            virtual void WeaponInitialize(Characters::Player *pP) = 0;
            void updateSprite(const float dt) = 0;
            virtual void update(const float dt) = 0;

            void colide(Entity *other, TupleF intersec) override {}
            void moveOnColision(Entity *other) override {}
            void execute() override {}
        };
    }
}