/* #pragma once

#include "States/State.hpp"

#include "Entities/Characters/Player.hpp"
#include "GraphElements/StaticAnimation.hpp"
#include "Utilis/EntityList.hpp"
#include "Managers/ColisionManager.hpp"
#include "Managers/GraphicManager.hpp"
#include "Utilis/Tuple.hpp"
#include "States/StateMachine.hpp"

namespace States
{

    class Level : public State
    {
    private:
        Entities::Characters::Player *player;
        GraphicalElements::StaticAnimation background;
        List::EntityList *staticEntitiesList;
        List::EntityList *movingEntitiesList;
        Managers::Collision collisionManager;
        Managers::Graphics *pGraphicM;
        bool levelEnded;
        int playerPoints;
        TupleF nextPositionToRender;

    public:
        Level(StateMachine *pSM = nullptr);

        ~Level();

        void update(const float dt);

        void render();

        void resetState();

        void endLevel();

        int getPlayerPoints() const;

        void coinBomb(TupleF position);
    };

} // namespace States

*/