#pragma once

#include "Entities/MovingEntity.hpp"

namespace Entities
{
    class Projectile : public MovingEntity
    {
    private:
        sf::RectangleShape projectileShape; // Forma usada para desenhar o projétil
        bool active;                        // Estado de ativação do projétil

    public:
        Projectile(TupleF _position, TupleF _velocity, sf::Color color);
        ~Projectile();
        void update(float dt) override;

        void render(sf::RenderWindow &window) const;

        // Desenha o projétil diretamente
        void draw(sf::RenderWindow &window) const;

        // Define a cor do projétil
        void setColor(sf::Color color);

        // Retorna o status de ativação do projétil
        bool isActive() const;

        sf::RectangleShape getShape() const;

        void collide(Entity *otherEntity, TupleF intersect) override;
        void updateSprite(const float dt) override;
        void execute() override;
    };
}