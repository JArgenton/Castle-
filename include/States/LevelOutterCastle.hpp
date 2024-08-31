#pragma once
#include "States/Level.hpp"
namespace States
{

    class OutterCastle : public Level
    {
    private:
        static List::EntityList movingEntities;
        List::EntityList obstacles;

        bool levelEnded;

        int player1Points;
        int player2Points;

    public:
        OutterCastle(StateMachine *pSM = nullptr);

        ~OutterCastle();

        void createFase(const std::string &path);

        void resetState();

        void endLevel();

        int getPlayerPoints() const;

        void clearState();

        void createHardEnemys();

        void crateEasyObstacles();
    };

} // namespace States
