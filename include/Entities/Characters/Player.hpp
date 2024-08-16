#include "Character.hpp"
#include "Utilis/Coord.hpp"
using namespace Utilis;

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
            void initialize() override; // carrega as texturas
            void render();              // atualiza posiçao da imagem

            /*Colisions*/
            void moveOnColision(Entity *other); /*TODO classe Entity other*/

            /*GAME*/
            void update(const float dt);
        };
    }
}