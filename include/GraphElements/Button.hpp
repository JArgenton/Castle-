#pragma once
#include "GraphElements/Text.hpp"
#include "Ent.hpp"

namespace GraphicalElements
{

    class Button : public Ent
    {
    private:
        Text textInfo;
        sf::Texture *defaultTexture;
        sf::Texture *selectedTexture;

    public:
        Button(TupleF position = TupleF(0, 0), string info = "");

        ~Button();

        void select(const bool isSelected);

        void render();

        void execute() override {}
        void initialize() override {}
    };

} // namespace GraphicalElements