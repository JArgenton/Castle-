#include "Entities/Characters/Character.hpp"

namespace Entities
{

    namespace Characters
    {

        Character::Character(Coordinates::CoordF _position, Entities::ID _id) : MovingEntity(_position, _id),
                                                                                health(),
                                                                                flagcanAtk(true),
                                                                                flagIsAtking(false),
                                                                                coolDownTimer(0.0f),
                                                                                atkTimer(0.0f),
                                                                                atkRange(),
                                                                                atkDamage(),
                                                                                atkCooldown(),
                                                                                atkDuration()

        {
        }

        Character::~Character() {}

        /*SETs*/
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
        void Character::set_atkRange(float _Range)
        {
            atkRange = _Range;
        }
        void Character::set_atkDamage(int _damage)
        {
            atkDamage = _damage;
        }

        /*gets*/
        int Character::get_health()
        {
            return health;
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
            health = health - dmg;
            if (health <= 0)
            {
                active = false;
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
            } //
            else
            {
                coolDownTimer += dt;
                atkTimer = 0;
            }
        }
        const bool Character::canAtk()
        {
            return coolDownTimer > atkCooldown ? true : false;
        }
        bool Character::isAtking()
        {
            return flagIsAtking;
        }
    }
}