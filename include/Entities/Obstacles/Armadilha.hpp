#pragma once
#include "Entities/StaticEntity.hpp"
namespace Entities
{
    namespace Obstacles
    {
        class Armadilha : public StaticEntity
        {
        private:
            static std::string texturepath;

        public:
            Armadilha(TupleF _position = TupleF(90.0f, 100.0f));
            ~Armadilha();
            void initialize();
            unsigned int getDamage() const;
        };
    }
}