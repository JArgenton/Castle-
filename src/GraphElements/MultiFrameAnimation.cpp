#include "GraphElements/MultiFrameAnimation.hpp"

namespace GraphicalElements
{

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

    void MultiFrameAnimation::addNewAnimation(AnimationID, string path, int imageCount, float switchTime)
    {
    }
    void MultiFrameAnimation::update(AnimationID id, bool facingLeft, TupleF _position, float dt)
    {
    }

} // namespace GraphicalElements
