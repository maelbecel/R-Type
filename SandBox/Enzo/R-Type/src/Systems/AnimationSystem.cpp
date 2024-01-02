/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"
#include "Components/Animation.hpp"

namespace RType {

    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void AnimationSystem::Update(World *world, Timestep ts)
    {
        world->ForEach<AnimationComponent, SpriteRendererComponent>([&](Entity *entity, ComponentHandle<AnimationComponent> animation, ComponentHandle<SpriteRendererComponent> sprite) {
            AnimationComponent      &ac = animation.Get(); // ac = Animation Component
            SpriteRendererComponent &sc = sprite.Get();    // sc = SpriteRenderer Component

            if (ac.IsPlaying == false || ac.Frames.size() == 0)
                return;
            float frameDuration = 1.0f / ac.FrameRate;

            ac.FrameTimer += ts;

            if (ac.FrameTimer >= frameDuration) {
                int frameToAdvance = static_cast<int>(ac.FrameTimer / frameDuration);

                ac.FrameTimer       -= (float)frameToAdvance * frameDuration;
                ac.CurrentFrameIndex = (ac.CurrentFrameIndex + 1) % ac.Frames.size();
                sc.Texture           = ac.Frames[ac.CurrentFrameIndex];

                if (ac.CurrentFrameIndex == ac.Frames.size() - 1) {
                    ac.CurrentFrameIndex = 0;
                    ac.FrameTimer        = 0.0f;
                }

                if (ac.Repeat == false && ac.CurrentFrameIndex == ac.Frames.size() - 1) {
                    ac.IsPlaying = false;

                    world->Emit<Events::AnimationEndingEvent>({ entity });
                }
            }
        });
    }

    void AnimationSystem::Receive(UNUSED(World *world), UNUSED(const Events::AnimationEndingEvent &event))
    {
        // If the animation need to call a specific event when it ends, it will be here
    }
};
