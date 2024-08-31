#pragma once
#include "States/Level.hpp"
#include "Entities/Characters/Enemies/BigBoss.hpp"

namespace States
{

    class InnerCastle : public Level
    {
    private:
        const int maxArchers;
        Characters::Enemies::BigBoss *boss;

    public:
        InnerCastle(StateMachine *pSM = nullptr);

        ~InnerCastle();

        void createFase(const std::string &path);
        void resetState();
        void endLevel();
        void clearState();
        // funções usadas para salvar level
        void CreateHardEnemy();
    };

} // namespace States
