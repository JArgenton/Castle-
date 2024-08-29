#pragma once

#include "Ent.hpp"

namespace GraphicalElements
{
    class HealthBar : public Ent
    {
    private:
        sf::Texture *texture;
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