#include "Entities/Characters/Character.hpp"

namespace Entities{

    namespace Characters{

        Character::Character(Coordinates::CoordF psize,
        Coordinates::CoordF pposition,
        Coordinates::CoordF pvelocity,
        float phealth,
        float patkCooldown,
        float patkDuration,
        float patkRange,
        int patkDamage,
        Entities::ID id
        ): 
        MovingEntity(psize, pposition, pvelocity, id),
        health(phealth),
        atkCooldown(patkCooldown),
        atkDuration(patkDuration),
        atkRange(patkRange),
        atkDamage(patkDamage),
        flagcanAtk(true)
        { }

        Character::~Character(){ }

        /*SETs*/
        void Character::set_health(int phealth){
            health = phealth;
        }
        void Character::set_atkCooldown(float pCooldown){
            atkCooldown = pCooldown;
        }
        void Character::set_atkDuration(float pDuration){
            atkDuration = pDuration;
        }
        void Character::set_atkRange(float pRange){
            atkRange = pRange;
        }
        void Character::set_atkDamage(int pdamage){
            atkDamage = pdamage;
        }
        
        /*gets*/
        int Character::get_health(){
            return health;
        }

        /*Actions*/
        void Character::atack(){
            if(canAtk()){
                flagIsAtking = true;
            }
            

        }
        void Character::reciveDmg(int dmg){
            health = health - dmg;
            if(health <= 0){
                active = false;
            }
        }
        


        /*timers & conditions*/
        void Character::incrementAtkTimer(const float dt){
            if (flagIsAtking) {
                coolDownTimer = 0;
                atkTimer += dt;
                if (atkTimer > atkDuration)
                    flagIsAtking = false;
            } //
            else {
                coolDownTimer += dt;
                atkTimer = 0;
            }
        }
        const bool Character::canAtk(){
            return coolDownTimer > atkCooldown ? true : false;
        }
        bool Character::isAtking(){
            return flagIsAtking;
        }
    }
}