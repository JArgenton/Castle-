#pragma once
#include "States/Level.hpp"
namespace States
{

    class InnerCastle : public Level
    {
    private:
        static List::EntityList movingEntities;
        List::EntityList obstacles;

        bool levelEnded;

        int player1Points;
        int player2Points;

    public:
        InnerCastle(StateMachine *pSM = nullptr);

        ~InnerCastle();

        void createFase(const std::string &path);

        void resetState();

        void endLevel();

        int getPlayerPoints() const;

        void clearState();

        void createEasyEnemys();

        void crateHardObstacles();
    };

} // namespace States
