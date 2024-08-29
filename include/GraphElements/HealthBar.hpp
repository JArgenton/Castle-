#pragma once

#include "Ent.hpp"

namespace GraphicalElements
{

    enum HealthBarID
    {
        EMPTY = 0,
        FULL
    };

    class HealthBar : public Ent
    {
    private:
        sf::Texture *texture;
        sf::RectangleShape *body;
        int numStages;
        int stageWidth;
        int stageHeight;

    public:
        HealthBar();
        ~HealthBar();

        void initialize() override {}
        void execute() override {}

        void update(float healthPercentage, TupleF position); // Atualiza com a porcentagem de saúde
        void render();
    };

}