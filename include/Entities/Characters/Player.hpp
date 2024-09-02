#pragma once
#include "Character.hpp"
#include "Math/Tuple.hpp"
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
            bool fullyCreated;
            bool pointsGranted;

            static bool PlayerCreationFlag;
            const float dmgCooldown; // tempo para tomar dano novamente
            int points;

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
            void setPoints(int points);
            static void disablePlayerCreationFlag();
            void setFullyCreated(bool fullyCreated);

            /*GETs*/
            Weapons::Weapon *get_weapon();
            int getPoints();
            const int getTotalHealth() const;

            /*actions*/
            void atack();
            void jump();
            void walk(bool toLeft);
            void stop();

            void incrementPoints(const int points);

            /*visuals*/
            void execute();
            void initialize(); // carrega as texturas
            void initializeAfterLoad();

            /*Colisions*/
            void moveOnColision(Entity *other, TupleF intersection);
            void collide(Entity *other, TupleF intersec);
            /*GAME*/
            void updateSprite(const float dt);
            void update(const float dt);
        };
    }
}