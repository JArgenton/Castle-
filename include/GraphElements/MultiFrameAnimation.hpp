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
        reciveDamage,
        jump,

    };

    class MultiFrameAnimation : public Ent
    {
    private:
        std::map<AnimationID, AnimationFrame *> animationMap;
        AnimationID CurrentID;

    public:
        MultiFrameAnimation();

        ~MultiFrameAnimation();
        void execute() override {}
        void initialize() override {}
        void addNewAnimation(AnimationID, string path, int imageCount, float switchTime);
        void update(AnimationID id, bool facingLeft, TupleF _position, float dt);
        void setSize(float tam1, float tam2);
        void setRotation(float angle);
        void setBodyScale(float tam1, float tam2);
    };

} // namespace GraphicalElements