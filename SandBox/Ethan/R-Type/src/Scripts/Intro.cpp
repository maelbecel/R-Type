/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Intro
*/

#include "Intro.hpp"

namespace RType {
    
    using namespace Exodia;

    /////////////
    // Methods //
    /////////////

    void Intro::OnCreate()
    {
        AnimationComponent animIn;
        AnimationComponent animOut;

        std::vector<Ref<SubTexture2D>> framesIn;
        for (uint32_t x = 0; x < 4; x++)
            framesIn.push_back(SubTexture2D::CreateFromCoords(LIFTIN, { x * 128, 0 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        for (uint32_t y = 3; y > 0; y--) {
            for (uint32_t x = 0; x < 4; x++)
                framesIn.push_back(SubTexture2D::CreateFromCoords(LIFTIN, { x * 128, y * 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
        }

        std::vector<Ref<SubTexture2D>> framesOut;
        for (uint32_t y = 0; y < 2; y++) {
            for (uint32_t x = 0; x < 4; x++) {
                if (y == 0 && x == 3)
                    continue;
                framesOut.push_back(SubTexture2D::CreateFromCoords(LIFTOUT, { x * 128, y * 128 }, { 1.0f, 1.0f }, { 128.0f, 128.0f }));
            }
        }

        animIn.Frames     = framesIn;
        animOut.Frames    = framesOut;
        animIn.IsPlaying  = false;
        animIn.Repeat     = true;
        animIn.FrameRate  = 7.0f;
        animOut.IsPlaying = false;
        animOut.Repeat    = true;
        animOut.FrameRate = 7.0f;

        _Animations.push_back(animIn);
        _Animations.push_back(animOut);
    }

    void Intro::OnUpdate(Timestep ts)
    {
        _Time += ts;

        if (_Time >= TimeBetweenAnimations) {
            _Time = 0.0f;

            auto anim   = GetComponent<AnimationComponent>();
            auto sprite = GetComponent<SpriteRendererComponent>();

            if (!sprite)
                sprite = HandleEntity->AddComponent<SpriteRendererComponent>();
            if (!anim) {
                _Animations[0].IsPlaying = true;

                anim = HandleEntity->AddComponent<AnimationComponent>(_Animations[0]);

                sprite.Get().Texture = anim.Get().Frames[0];
            } else {
                if (_IsLiftIn) {
                    _Animations[0].IsPlaying = false;
                    _Animations[1].IsPlaying = true;

                    anim.Get() = _Animations[1];
                    sprite.Get().Texture = anim.Get().Frames[0];

                    _IsLiftIn = false;
                } else {
                    _Animations[0].IsPlaying = true;
                    _Animations[1].IsPlaying = false;

                    anim.Get() = _Animations[0];
                    sprite.Get().Texture = anim.Get().Frames[0];

                    _IsLiftIn = true;
                }
            }
        }
    }
}
