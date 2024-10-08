#pragma once
#include "Entities/MovingEntity.hpp"

namespace Entities
{

    namespace Characters
    {

        class Character : public MovingEntity
        {
        protected:
            int health;
            /*actions*/
            bool flagcanAtk;

            /*flags*/
            bool flagIsAtking;

            /*Timers*/
            float coolDownTimer; // timer para atacar novamente
            float atkTimer;      // timer para finalizar animaçao de ataque

            /*Attack propreties*/
            int atkDamage;

            /*Cooldowns (const)*/
            float atkCooldown; // tempo para atacar novamente
            float atkDuration; // tempo para finalizar a animaçao de ataque
            float dmgTimer;    // timer para tomar dano novamente
            float dmgCooldown;

            float trapTimmer;
            float trapedDuration;

        public:
            Character(TupleF _position = TupleF(0.0f, 0.0f), Entities::ID id = empty);

            virtual ~Character();

            /*SETs*/
            void set_health(int _healt);
            void set_atkCooldown(float _Cooldown);
            void set_coolDownTimer(float _Timer);
            void set_atkDuration(float _Duration);
            void set_atkRange(float _Range);
            void set_atkDamage(int _damage);
            void set_isAtking(bool _isAtking);

            /*gets*/
            int getHealth();
            int getAtkDamage();
            float getCoolDownTimer();
            float getAtkCooldown();
            float getTrapDuration();
            float getTrapTimmer();

            /*Actions*/
            virtual void atack();
            virtual void reciveDmg(int dmg);
            virtual void collide(Entity *other, TupleF intersec) = 0;

            /*visuals*/
            virtual void initialize() = 0; // carrega as texturas

            /*timers & conditions*/
            virtual void incrementAtkTimer(const float dt); // necessario devido a decisao de separ o tempo atacando e de cooldown do atk, add o dt no contador correto
            void incrementDmgTimer(const float dt);
            const bool canAtk(); // necessario devido a decisao de separ o tempo atacando e de cooldown do atk, muda o booleano
            const bool canReciveDmg();
            bool isAtking();

            /*update*/
            virtual void update(const float dt) = 0;
            void isTraped(float time);
            bool canMove();
        };
    }
}