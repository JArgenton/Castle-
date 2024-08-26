/* #include "States/Level.hpp"

#include "Entities/Obstacles/Plataforma.hpp"

namespace States
{

    Level::Level(StateMachine *pSM) : State(pSM, stateID::PLAYING),
                                      staticEntitiesList(),
                                      movingEntitiesList(),
                                      collisionManager(movingEntitiesList, staticEntitiesList),
                                      pGraphicM(Managers::Graphics::get_instance())
    {
    }
    Level::~Level()
    {
    }

    void Level::update(const float dt)
    {
        for (unsigned int i = 0; i < movingEntitiesList->getSize(); i++)
        {
            movingEntitiesList[i]->update(dt);
        }

        collisionManager.collide();

        pGraphicM->centerView(TupleF(player->getPosition().x, pGraphicM->getWindowSize().y / 2 - PLATFORM_HEIGHT / 2));
        background.update(TupleF(player->getPosition().x, pGraphicM->getWindowSize().y / 2 - PLATFORM_HEIGHT / 2));
        hud.update(dt);

        if (player->getPosition().x >= nextPositionToRender.x)
            worldGen.generate(&nextPositionToRender, player);

        if (!player->isActive())
        {
            endLevel();
            changeState(States::stateID::gameOver);
        }
    }

    void Level::render()
    {

        background.render();

        for (unsigned int i = 0; i < staticEntitiesList.getSize(); i++)
        {
            staticEntitiesList[i]->render();
        }

        for (unsigned int i = 0; i < movingEntitiesList.getSize(); i++)
        {
            movingEntitiesList[i]->render();
        }

        hud.render();
    }

    void Level::resetState()
    {
        if (levelEnded)
        {

            player = new Entities::Characters::Player(TupleF(200.f, 300.f));
            movingEntitiesList.addEntity(player);

            worldGen.resetToOrigin();

            worldGen.generate(&nextPositionToRender, player);

            hud.setPlayer(player);

            levelEnded = false;
        }
        worldGen.setRenderDistance();
    }

    void Level::endLevel()
    {
        playerPoints = player->getPlayerPoints();
        movingEntitiesList.cleanList();
        staticEntitiesList.cleanList();
        levelEnded = true;
    }

    int Level::getPlayerPoints() const
    {
        return playerPoints;
    }

    void Level::coinBomb(TupleF position)
    {
        worldGen.explodeCoins(position);
    }

} // namespace States
*/