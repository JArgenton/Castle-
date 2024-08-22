#include "Character.hpp"
#include "Utilis/Tuple.hpp"
using namespace Tuples;

namespace Entities
{
    namespace Weapons
    {
        class Weapon; // Declaração de classe avançada
    }

    namespace Characters
    {

        class Player : public Character
        {
        private:
            const float dmgCooldown; // tempo para tomar dano novamente

            /*actions*/
            bool canWalk;
            bool canReciveDmg;
            bool canJump;

            /*conditions*/
            bool isMoving;

            /*cooldowns*/

            /*timers*/
            float dmgTimer; // timer para tomar dano novamente

            /*weapon*/
            Weapons::Weapon *weapon;

        public:
            Player(Weapons::Weapon *pW = nullptr);
            ~Player();

            /*SETs*/
            void set_weapon(Weapons::Weapon *pweapon);
            void setJump(bool jump);
            void setWalk(bool walk);

            /*GETs*/
            Weapons::Weapon *get_weapon();

            /*actions*/
            void atack();
            void reciveDmg(int dmg);
            void jump();
            void walk(bool toLeft);
            void stop();

            /*visuals*/
            void execute();
            void initialize(); // carrega as texturas
            /*Colisions*/
            void collide(Entity *other, TupleF intersec);
            /*GAME*/
            void updateSprite(const float dt);
            void update(const float dt);
        };
    }
}