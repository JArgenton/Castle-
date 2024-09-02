#include "GraphElements/MultiFrameAnimation.hpp"

namespace GraphicalElements
{
    /*CLASSE BASEADA NA IMPLEMENTAÇAO DO MONITOR BURDA*/

    std::map<AnimationID, AnimationFrame *> animationMap;
    AnimationID CurrentID;

    MultiFrameAnimation::MultiFrameAnimation() : animationMap(),
                                                 CurrentID(AnimationID::idle)
    {
    }

    MultiFrameAnimation::~MultiFrameAnimation()
    {
        std::map<AnimationID, AnimationFrame *>::iterator it;
        for (it = animationMap.begin(); it != animationMap.end(); it++)
        {
            delete it->second;
        }
        animationMap.clear();
    }

    void MultiFrameAnimation::addNewAnimation(AnimationID id, string path, int imageCount, float switchTime)
    {
        AnimationFrame *temp = new AnimationFrame(path, imageCount, switchTime);
        if (temp)
        {
            animationMap.insert(std::pair<AnimationID, AnimationFrame *>(id, temp));
            sf::IntRect rectSize = temp->getSize();
            body->setSize(sf::Vector2f(rectSize.width, rectSize.height));
            body->setOrigin(sf::Vector2f(rectSize.width, rectSize.height) / 2.0f);
        }
    }
    void MultiFrameAnimation::update(AnimationID id, bool facingLeft, TupleF _position, float dt)
    {
        if (CurrentID != id)
        {
            CurrentID = id;
            animationMap[CurrentID]->reset();
        }
        animationMap[CurrentID]->update(dt, facingLeft);
        body->setPosition(sf::Vector2f(_position.x, _position.y));
        body->setTextureRect(animationMap[CurrentID]->getSize());

        body->setTexture(animationMap[CurrentID]->getTexture());
    }
    void MultiFrameAnimation::setBodyScale(float tam1, float tam2)
    {
        body->setScale(tam1, tam2);
    }
    void MultiFrameAnimation::setSize(float tam1, float tam2)
    {
        body->setSize(sf::Vector2f(tam1, tam2));
    }
    void MultiFrameAnimation::setRotation(float angle)
    {
        body->setRotation(angle);
    }

} // namespace GraphicalElements
