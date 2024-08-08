#pragma once
#include "Entities/Entity.hpp"
#include <iostream>
using namespace std;

namespace Entities
{

    namespace Weapons
    {

        enum Type
        {
            empty = 0,
            sword,
            spear,
            bow
        };
        class Weapon : public MovingEntity
        {
        protected:
            /*Cooldowns (const)*/
            Characters::Player *pPlayer;
            Type type;
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
            virtual void initialize(Characters::Player *pP) = 0;
        };
    }
}