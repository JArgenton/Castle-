#pragma once
#include "AnimationFrame.hpp"
#include <map>
#include "GraphElements/AnimationFrame.hpp"
#include "Ent.hpp"

namespace GraphicalElements
{
    enum AnimationID
    {
        walk = 0,
        idle,
        attack,
        cooldown,

        run, // soldado corre perto de player
    };

    class MultiFrameAnimation : public Ent
    {
    private:
        std::map<AnimationID, AnimationFrame *> animationMap;
        AnimationID CurrentID;

    public:
        MultiFrameAnimation();

        ~MultiFrameAnimation();

        void addNewAnimation(AnimationID, string path, int imageCount, float switchTime);
        void update(AnimationID id, bool facingLeft, TupleF _position, float dt);
    };

} // namespace GraphicalElements