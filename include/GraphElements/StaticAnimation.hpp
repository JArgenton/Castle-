#pragma once

#include "Ent.hpp"

namespace GraphicalElements
{

    class StaticAnimation : public Ent
    {
    private:
        sf::Texture *texture;

    public:
        StaticAnimation();

        virtual ~StaticAnimation();

        void initialize(const char *path, TupleF position, TupleF size);

        void update(TupleF position);

        void execute() override {}
        void initialize() override {}
    };

} // namespace GraphicalElements