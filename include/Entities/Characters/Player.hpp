#pragma once
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
            static bool PlayerCreationFlag;
            const float dmgCooldown; // tempo para tomar dano novamente
            unsigned int points;
            bool fullyCreated;
            /*actions*/
            bool canWalk;
            bool canJump;

            /*conditions*/
            bool isMoving;

            /*weapon*/
            Weapons::Weapon *weapon;

        public:
            Player(TupleF _position, Weapons::Weapon *pW = nullptr, ID _id = PLAYER1);
            ~Player();
            bool getFullyCreated();
            /*SETs*/
            void set_weapon(Weapons::Weapon *pweapon);
            void setJump(bool jump);
            void setWalk(bool walk);

            /*GETs*/
            Weapons::Weapon *get_weapon();
            const int getPoints() const;

            /*actions*/
            void atack();
            void jump();
            void walk(bool toLeft);
            void stop();
            void incrementPoints(const int points);

            /*visuals*/
            void execute();
            void initialize(); // carrega as texturas
            /*Colisions*/
            void moveOnColision(Entity *other, TupleF intersection);
            void collide(Entity *other, TupleF intersec);
            /*GAME*/
            void updateSprite(const float dt);
            void update(const float dt);
        };
    }
}