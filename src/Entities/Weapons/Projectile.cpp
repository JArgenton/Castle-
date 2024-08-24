#include "Entities/Weapons/Projectile.hpp"

#define PROJECTILE_DMG 10.0f
#define TIME_LIMIT_SCREEN 50.0f

namespace Entities
{

    Projectile::Projectile(TupleF _position, TupleF _velocity, sf::Color color)
        : MovingEntity(_position, PROJECTILE), active(true), timeInScreen(0.0)
    {
        set_velocity(_velocity); // Define a velocidade

        // Configura o RectangleShape do projétil
        projectileShape.setSize(sf::Vector2f(10.0f, 5.0f)); // Define o tamanho do projétil
        projectileShape.setFillColor(color);                // Define a cor do projétil
        projectileShape.setPosition(_position.x, _position.y);
    }

    Projectile::~Projectile()
    {
    }

    const float Projectile::getDamage()
    {
        return PROJECTILE_DMG;
    }

    void Projectile::update(float dt)
    {
        timeInScreen += dt;

        // Desativa o projétil se o tempo em tela ultrapassar o limite
        if (timeInScreen > TIME_LIMIT_SCREEN)
        {
            active = false;
        }

        // Atualiza a posição do projétil com base na velocidade e delta time
        TupleF velocity = get_velocity();
        TupleF newPosition = getPosition();
        velocity.y += GRAVITY;
        newPosition.x += velocity.x * dt;
        newPosition.y += velocity.y * dt * 3;
        setPosition(newPosition);

        // Atualiza a posição do RectangleShape do projétil
        projectileShape.setPosition(newPosition.x, newPosition.y);

        // Remove a renderização se o projétil estiver inativo
        if (active)
        {
            Managers::Graphics *gpManager = Managers::Graphics::get_instance();
            sf::RectangleShape shape = this->getShape();
            gpManager->render(&shape);
        }
    }

    void Projectile::render(sf::RenderWindow &window) const
    {
        if (active)
        {
            window.draw(projectileShape);
        }
    }

    void Projectile::draw(sf::RenderWindow &window) const
    {
        if (active)
        {
            // Desenha o RectangleShape diretamente na janela
            window.draw(projectileShape);
        }
    }

    void Projectile::setColor(sf::Color color)
    {
        projectileShape.setFillColor(color); // Define a cor do projétil
    }

    bool Projectile::isActive() const
    {
        return active; // Retorna o estado de ativação do projétil
    }

    void Projectile::collide(Entity *otherEntity, TupleF intersect)
    {
        moveOnColision(otherEntity, intersect);

        switch (otherEntity->getId())
        {
        case ID::PLAYER1:
        {
            active = false;
            break;
        }
        case ID::PLAYER2:
        {
            active = false;
            break;
        }
        case ID::PLATAFORMA:
        {
            active = false;
            break;
        }
        case ID::LAVA:
        {
            active = false;
            break;
        }

        default:
        {
            this->active = false;
            break;
        }
        }
    }

    /*void Projectile::updateSprite(const float dt)
    {
        // Atualizar a aparência do projétil se necessário
    }*/

    void Projectile::execute()
    {
        // Executar a lógica específica do projétil
    }

    const sf::RectangleShape Projectile::getShape() const
    {
        return projectileShape;
    }
}
