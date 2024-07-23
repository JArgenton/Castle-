#pragma once
#include "Entities/Entity.hpp"
#include <iostream>
using namespace std;

namespace Entities{
    
    namespace Weapons{

        enum Type{
            empty = 0,
            sword,
            spear,
            bow
        };

        class Weapon
        {
        protected:
            /*Cooldowns (const)*/
            Type type;
        public:
            Weapon();
            ~Weapon();
            virtual void atack() = 0;
            virtual void drop() = 0;
            virtual const float atkCooldown() = 0; // tempo para atacar novamente
            virtual const float atkDuration() = 0; // tempo para atacar novamente
            virtual const float atkRange() = 0;
            virtual const int atkDamage() = 0;
        };    
    }
}