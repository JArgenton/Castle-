#pragma once
#include "States/Level.hpp"
#include "Entities/Characters/Enemies/EliteKnight.hpp"

namespace States
{

    class InnerCastle : public Level
    {
    private:
        const int maxArchers;
        Characters::Enemies::EliteKnight *boss;

    public:
        InnerCastle(StateMachine *pSM = nullptr);

        ~InnerCastle();
        void executar();
        void createFase(const std::string &path);
        void resetState();
        void endLevel();
        void clearState();
        // funções usadas para salvar level
        void CreateHardEnemy();
    };

} // namespace States
