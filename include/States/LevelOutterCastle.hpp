#pragma once
#include "States/Level.hpp"
namespace States
{

    class OutterCastle : public Level
    {
    private:
        int maxEasyEnemies;

    public:
        OutterCastle(StateMachine *pSM);
        ~OutterCastle();

        void createFase(const std::string &path);
        void resetState();
        void endLevel();
        void clearState();
        // funções usadas para salvar level

        void CreateEasyEnemy();
        void CreateHardObstacle();

        void executar();
    };

} // namespace States
