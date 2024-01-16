/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Intro
*/

// R-Type includes
#include "Intro.hpp"
#include "Component/Fade.hpp"

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
            _Time   = 0.0f;
            _IsLoad = true;

            auto &sprite = GetComponent<SpriteRendererComponent>();

            if (!HandleEntity.HasComponent<AnimationComponent>()) {
                _Animations[0].IsPlaying = true;

                auto &anim = HandleEntity.AddComponent<AnimationComponent>(_Animations[0]);

                sprite.Texture = anim.Frames[0];

                PressStartFactory();
            } else {
                auto &anim = GetComponent<AnimationComponent>();

                if (_IsLiftIn) {
                    _Animations[0].IsPlaying = false;
                    _Animations[1].IsPlaying = true;

                    anim = _Animations[1];
                    sprite.Texture = anim.Frames[0];

                    _IsLiftIn = false;
                } else {
                    _Animations[0].IsPlaying = true;
                    _Animations[1].IsPlaying = false;

                    anim = _Animations[0];
                    sprite.Texture = anim.Frames[0];

                    _IsLiftIn = true;
                }
            }
        }
    }

    void Intro::OnKeyPressed(int keycode)
    {
        // Wait the first animation to be done before skipping it
        if (!_IsLoad)
            return;

        // If start is pressed, we fade out the background and the text for doing a transition to the menu
        if (keycode == Key::ENTER) {
            if (!HandleEntity.HasComponent<FadeComponent>())
                HandleEntity.AddComponent<FadeComponent>(0.0f, 0.4f, 0.4f);

            auto &fade = GetComponent<FadeComponent>();

            fade.ShouldFadeIn  = false;
            fade.ShouldFadeOut = true;
            fade.Repeat        = false;

            Scene *scene = HandleEntity.GetScene();

            if (!scene)
                return;
            GameObject entity = scene->GetEntityByName("Background");

            if (!entity)
                return;
            if (!entity.HasComponent<FadeComponent>())
                entity.AddComponent<FadeComponent>(0.0f, 0.4f, 0.4f);

            auto &fadeText = entity.GetComponent<FadeComponent>();

            fadeText.ShouldFadeIn  = false;
            fadeText.ShouldFadeOut = true;
            fadeText.Repeat        = false;
        }
    }

    void Intro::PressStartFactory()
    {
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject entity = scene->LoadPrefabs((Project::GetActiveAssetDirectory() / "Prefabs/Menu/PressStart.prefab").string(), true);

        if (!entity)
            return;
        auto &transform = entity.GetComponent<TransformComponent>();

        transform.Translation = { -1.25f, 0.00f, 0.0f };
    }
}
