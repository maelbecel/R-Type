/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentExample
*/

#ifndef ANIMATIONCOMPONENT_HPP_
#define ANIMATIONCOMPONENT_HPP_

#include "Exodia.hpp"

namespace Exodia {

    /**
     * @brief Animation component.
     *
     * @param CurrentFrame Current frame of the animation.
     * @param MaxFrame Max frame of the animation.
     * @param FrameTime Time between each frame.
     */
    struct Animation : public Component {
        float CurrentFrame;
        float MaxFrame;
        float FrameTime;
        float ElapsedTime = 0.0f;

        Animation(const Animation &) = default;
        Animation(float CurrentFrame = 0.0f, float MaxFrame = 0.0f, float FrameTime = 0.0f)
            : CurrentFrame(CurrentFrame), MaxFrame(MaxFrame), FrameTime(FrameTime){};

        virtual void Serialize(UNUSED(YAML::Emitter &out)) override{};
    };
}; // namespace Exodia

#endif /* !ANIMATIONCOMPONENT_HPP_ */
