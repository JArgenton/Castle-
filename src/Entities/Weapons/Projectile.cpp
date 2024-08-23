#include "Entities/Weapons/Projectile.hpp"

namespace Entities
{

    Projectile::Projectile(TupleF _position, TupleF _velocity, sf::Color color)
        : MovingEntity(_position, PROJECTILE), active(true)
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

    void Projectile::update(float dt)
    {
        if (active)
        {
            // Atualiza a posição do projétil com base na velocidade e delta time
            TupleF velocity = get_velocity();
            TupleF newPosition = getPosition();
            newPosition.x += velocity.x * dt;
            newPosition.y += velocity.y * dt;
            setPosition(newPosition);

            // Atualiza a posição do RectangleShape do projétil
            projectileShape.setPosition(newPosition.x, newPosition.y);
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
        // Implementar a lógica de colisão
    }

    void Projectile::updateSprite(const float dt)
    {
        // Atualizar a aparência do projétil se necessário
    }

    void Projectile::execute()
    {
        // Executar a lógica específica do projétil
    }

    sf::RectangleShape Projectile::getShape() const
    {
        return projectileShape;
    }
}
