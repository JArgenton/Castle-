#pragma once

#include "Entities/StaticEntity.hpp"

namespace Entities
{
    namespace Obstacles
    {
        class Armadilha : public StaticEntity
        {
        private:
            // std::chrono::steady_clock::time_point endTime;
            bool delayStarted = false;
            bool paralized = false;

        public:
            Armadilha(TupleF _position = TupleF(90.0f, 100.0f));
            ~Armadilha();
            void initialize();
            unsigned int getDamage() const;
            void timeParalized(float dt);
        };
    } // namespace Obstacles

} // namespace Entities
