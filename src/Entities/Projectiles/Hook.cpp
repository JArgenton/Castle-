#include "Entities/Projectiles/Hook.hpp"
#include "Entities/Weapons/Sword.hpp"
#include "Math/geometry.hpp"
#define HOOK_SPEED 200.0f
using namespace GraphicalElements;

namespace Entities
{
    namespace Projectiles
    {

        Hook::Hook(TupleF _position) : Projectile(_position, ID::HOOK)
        {
        }

        Hook::~Hook()
        {
        }
        void Hook::initialize()
        {
            std::string path = "assets/Charge.png";

            setSize(30.0f, 50.0f);
            setDamage(15);
            damage = 10;
            active = true;

            SetTexture(path);

            body->rotate(90.0f);
            velocity(0.0f, 0.0f);
            sprite.addNewAnimation(AnimationID::attack, path, 9, 0.1);
        }

        void Hook::setDirection(TupleF _direction)
        {
            velocity = _direction;

            geometry::escalateVector(&velocity, HOOK_SPEED);
        }

        float Hook::getDirectionX()
        {
            geometry::NormalizeVector(&velocity);
            return velocity.x;
        }

        float Hook::getDirectionY()
        {
            geometry::NormalizeVector(&velocity);
            return velocity.y;
        }

        void Hook::update(float dt)
        {
            if (velocity.x > 0)
            {
                setFacing(true);
            }
            else
            {
                setFacing(false);
            }
            // Desativa o projétil se o tempo em tela ultrapassar o limite
            if (getPosition().y > 10000)
            {
                active = false;
            }

            // Atualiza a posição do projétil com base na velocidade e delta time
            velocity.y += GRAVITY * 0.2f;
            body->move(velocity.x * dt, velocity.y * dt);
            updateSprite(dt);

            render();
        }

        void Hook::collide(Entity *otherEntity, TupleF intersect)
        {
            active = false;
            moveOnColision(otherEntity, intersect);

            ID otherID = otherEntity->getId();
            if (otherID == WEAPON)
            {
                Characters::Player *pP = dynamic_cast<Weapons::Sword *>(otherEntity)->getOwner();
                if (!pP->isAtking())
                {
                    pP->reciveDmg(damage);
                    hook(pP);
                }
            }
        }
        void Hook::hook(Characters::Player *pP)
        {

            pP->isTraped(1.0f);
            if (isFacingLeft())
            {
                pP->set_velocity(TupleF(-100.0f, -40.0f));
            }
            else
            {
                pP->set_velocity(TupleF(100.0f, -40.0f));
            }
            pP->reciveDmg(25);
        }

    }
}