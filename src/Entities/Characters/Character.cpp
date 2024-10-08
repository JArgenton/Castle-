#include "Entities/Characters/Character.hpp"

namespace Entities
{

    namespace Characters
    {

        Character::Character(TupleF _position, Entities::ID _id) : MovingEntity(_position, _id),
                                                                   health(150),
                                                                   flagcanAtk(true),
                                                                   flagIsAtking(false),
                                                                   coolDownTimer(0.0f),
                                                                   atkTimer(0.0f),
                                                                   atkDamage(10),
                                                                   atkCooldown(0.0f),
                                                                   atkDuration(0.0f),
                                                                   dmgTimer(0.5f),
                                                                   dmgCooldown(0.5f),
                                                                   trapTimmer(1000.0f),
                                                                   trapedDuration(0.0f)

        {
        }

        Character::~Character() {}
        void Character::set_health(int _health)
        {
            health = _health;
        }

        void Character::set_atkCooldown(float _Cooldown)
        {
            atkCooldown = _Cooldown;
        }
        void Character::set_atkDuration(float _Duration)
        {
            atkDuration = _Duration;
        }
        void Character::set_atkDamage(int _damage)
        {
            atkDamage = _damage;
        }

        void Character::set_coolDownTimer(float _Timer)
        {
            coolDownTimer = _Timer;
        }

        void Character::set_isAtking(bool _isAtking)
        {
            flagIsAtking = _isAtking;
        }

        /*gets*/
        int Character::getHealth()
        {
            return health;
        }
        int Character::getAtkDamage()
        {
            return atkDamage;
        }

        float Character::getCoolDownTimer()
        {
            return coolDownTimer;
        }
        float Character::getAtkCooldown()
        {
            return atkCooldown;
        }
        float Character::getTrapDuration()
        {
            return trapedDuration;
        }
        float Character::getTrapTimmer()
        {
            return trapTimmer;
        }

        /*Actions*/
        void Character::atack()
        {
            if (canAtk())
            {
                flagIsAtking = true;
            }
        }
        void Character::reciveDmg(int dmg)
        {
            if (canReciveDmg())
            {
                health -= dmg;
                if (health <= 0)
                {
                    active = false;
                }
                dmgTimer = 0;
            }
        }

        /*timers & conditions*/
        void Character::incrementAtkTimer(const float dt)
        {
            if (flagIsAtking)
            {
                coolDownTimer = 0;
                atkTimer += dt;
                if (atkTimer > atkDuration)
                    flagIsAtking = false;
            }
            else
            {
                coolDownTimer += dt;
                atkTimer = 0;
            }
        }
        void Character::incrementDmgTimer(const float dt)
        {
            dmgTimer += dt;
        }

        const bool Character::canAtk()
        {
            return coolDownTimer > atkCooldown ? true : false;
        }

        const bool Character::canReciveDmg()
        {
            return dmgTimer > dmgCooldown ? true : false;
        }

        bool Character::isAtking()
        {
            return flagIsAtking;
        }
        void Character::isTraped(float time)
        {
            trapedDuration = time;
            trapTimmer = 0;
        }
        bool Character::canMove()
        {
            return trapTimmer > trapedDuration;
        }
    }
}
