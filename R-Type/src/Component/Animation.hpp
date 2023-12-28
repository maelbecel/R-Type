/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
    #define ANIMATION_HPP_

    // Exodia includes
    #include "Exodia.hpp"

    // External includes
    #include <vector>

namespace RType {

    /**
     * @brief Animation Component.
     *
     * This component represents an animation in the game.
     * It contains :
     * - A list of frames (in SubTexture2D format)
     * - A boolean indicating if the animation is playing
     * - A boolean indicating if the animation should repeat
     * - A float indicating the frame rate of the animation (in seconds) (FrameRate represents the time between each frame) (like Timestep)
     * - A float indicating the time since the last frame change (in seconds)
     * - An integer indicating the current frame of the animation
     */
    struct AnimationComponent : public Exodia::Component {
        std::vector<Ref<Exodia::SubTexture2D>> Frames; // !< List containing all the frames of the animation in SubTexture2D format

        bool IsPlaying; // !< Boolean indicating if the animation is playing
        bool Repeat; // !< Boolean indicating if the animation should repeat

        float FrameRate; // !< Float indicating the frame rate of the animation (in seconds) (FrameRate represents the time between each frame) (like Timestep)
        float FrameTimer; // !< Float indicating the time since the last frame change (in seconds)

        int CurrentFrameIndex; // !< Integer indicating the current frame of the animation

        AnimationComponent(const AnimationComponent &other) : Frames(other.Frames), IsPlaying(other.IsPlaying), Repeat(other.Repeat), FrameRate(other.FrameRate), FrameTimer(other.FrameTimer), CurrentFrameIndex(other.CurrentFrameIndex) {};
        AnimationComponent(const std::vector<Ref<Exodia::SubTexture2D>> &frames = {}) : Frames(frames), IsPlaying(false), Repeat(false), FrameRate(0.0f), FrameTimer(0.0f), CurrentFrameIndex(0) {};

        AnimationComponent &operator=(const AnimationComponent &other)
        {
            Frames            = other.Frames;
            IsPlaying         = other.IsPlaying;
            Repeat            = other.Repeat;
            FrameRate         = other.FrameRate;
            FrameTimer        = other.FrameTimer;
            CurrentFrameIndex = other.CurrentFrameIndex;

            return *this;
        }

        //TODO: Save in a file the animation
        //TODO: Load from a file the animation
        //TODO: Serialize the animation in a Buffer
        //TODO: Deserialize the animation from a Buffer
    };
};

#endif /* !ANIMATION_HPP_ */