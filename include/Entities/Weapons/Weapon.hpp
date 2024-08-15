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
            float AtkCooldown;
            float AtkDuration;
            float AtkRange;
            int AtkDamage;

        public:
            Weapon();
            virtual ~Weapon();
            virtual void atack() = 0;
            virtual const float getAtkCooldown(); // tempo para atacar novamente
            virtual const float getAtkDuration(); // tempo para atacar novamente
            virtual const float getAtkRange();
            virtual const int getAtkDamage();
            void setPlayer(Characters::Player *pP);
            virtual void WeaponInitialize(Characters::Player *pP) = 0;
        };
    }
}