#include "Entities/Characters/Player.hpp"
#define PLAYER_SIZE_X 100.0f
#define PLAYER_SIZE_Y 100.0f
#define PLAYER_VELOCITY 5.0f
#define PLAYER_HEALT 100
#define PLAYER_DMG_COOLDOWN 0.0f
#define JUMP_HEIGH 3.0f

namespace Entities{
    namespace Characters{

        Player::Player(Coordinates::CoordF pposition, Weapons::Weapon* pWeapon):
        Character(Coordinates::CoordF(PLAYER_SIZE_X, PLAYER_SIZE_Y), pposition, Coordinates::CoordF(PLAYER_VELOCITY, 0.0f), PLAYER_HEALT, 0.0f, 0.0f, 0.0f, 0, PLAYER),
        weapon(pWeapon),
        canJump(false),
        isMoving(false),
        canReciveDmg(false),
        dmgCooldown(PLAYER_DMG_COOLDOWN)
        { 

            if(weapon != nullptr){
                set_atkCooldown(weapon->atkCooldown());
                set_atkDuration(weapon->atkDuration());
                set_atkRange(weapon->atkRange());
                set_atkDamage(weapon->atkDamage());
            }
            dmgTimer = 0;            
        }

        Player::~Player(){
            weapon = nullptr;
        }

        /*SETs*/
        void Player::set_weapon(Weapons::Weapon* pweapon){
            weapon = pweapon;
        }

        /*GETs*/
        Weapons::Weapon* Player::get_weapon(){
            return weapon;
        }
        
        /*actions*/
        void Player::atack(){
            if(weapon != nullptr){
                weapon->atack();
            }
        }

        void Player::reciveDmg(int dmg){
            if(canReciveDmg){
                health -= dmg;
                if(health <= 0){
                 active = false;
                }
                dmgTimer = 0;
            }
            
        }
        void Player::colide(Entity* other, Coordinates::CoordF intersec){
            /*TODO*/
        }
        void Player::jump(){
            if(canJump){
                velocity.y = GRAVITY * 3;
            }
        }
        void Player::walk(bool toLeft){
            isMoving = true;
            facingLeft = toLeft;
        }
        void Player::stop(){
            isMoving = false;
        }

        /*visuals*/
        void Player::initialize(){
            image->initialize("PLAYERPATH", position, size);
        }
        void Player::render(){
            image->render();
        }

        /*Colisions*/
        void Player::moveOnColision(Entity* other){
                /*TODO*/
        }
        
        /*GAME*/
        void Player::update(const float dt){
            incrementAtkTimer(dt);

            if (isMoving) {
                velocity.x = PLAYER_VELOCITY;

                if (facingLeft)
                    velocity.x *= -1;
            }
            else
                velocity.x *= 0.5;
            velocity.y += GRAVITY * dt;

            position.x += velocity.x * dt;
            position.y += velocity.y * dt;

            image->update(position);
            render();

            dmgTimer += dt;

            if (position.y > 1000)
                active = false;
        }

 }
}