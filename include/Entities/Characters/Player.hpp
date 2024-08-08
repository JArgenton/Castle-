#include "Character.hpp"
#include "Utilis/Coord.hpp"
using namespace Utilis;

namespace Entities
{

    namespace Characters
    {

        class Player : public Character
        {
        private:
            /*weapon*/
            Weapons::Weapon *weapon;

            /*actions*/
            bool canWalk;
            bool canReciveDmg;
            bool canJump;

            /*conditions*/
            bool isMoving;

            /*cooldowns*/
            const float dmgCooldown; // tempo para tomar dano novamente

            /*timers*/
            float dmgTimer; // timer para tomar dano novamente

        public:
            Player();
            ~Player();

            /*SETs*/
            void set_weapon(Weapons::Weapon *pweapon);

            /*GETs*/
            Weapons::Weapon *get_weapon();

            /*actions*/
            void atack();
            void reciveDmg(int dmg);
            void colide(Entity *other, Coordinates::CoordF intersec);
            void jump();
            void walk(bool toLeft);
            void stop();

            /*visuals*/
            void initialize(); // carrega as texturas
            void render();     // atualiza posiçao da imagem

            /*Colisions*/
            void moveOnColision(Entity *other); /*TODO classe Entity other*/

            /*GAME*/
            void update(const float dt);
        };
    }
}