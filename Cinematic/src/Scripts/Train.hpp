/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef TRAIN_HPP_
#define TRAIN_HPP_

// Exodia includes
#include "Components/Animation.hpp"
#include "Exodia.hpp"

using namespace Exodia;

namespace Cinematic {

    class Train : public ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() {
            EXODIA_INFO("Train OnCreate");

            // Init Component
            HandleEntity.AddComponent<BoxCollider2DComponent>();
            HandleEntity.AddComponent<IDComponent>();
            HandleEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.0f));
            HandleEntity.AddComponent<SpriteRendererComponent>();
            HandleEntity.AddComponent<RigidBody2DComponent>();

            // Init Animation
            AnimationComponent anim;
            std::vector<Ref<SubTexture2D>> framesIdle;

            for (int i = 0; i < 8; i++)
                framesIdle.push_back(
                    SubTexture2D::CreateFromCoords(PATAPATA, {i, 0.0f}, {33.3125f, 36.0f}, {1.0f, 1.0f}));

            anim.Frames = framesIdle;
            anim.IsPlaying = false;
            anim.Repeat = true;
            anim.FrameRate = 13.2f;
            _Animations.push_back(anim);

            // Init Body
            auto &body = HandleEntity.AddComponent<RigidBody2DComponent>();

            body.Type = RigidBody2DComponent::BodyType::Dynamic;
            body.Mass = 0.0f;
            body.GravityScale = 0.0f;
            body.Velocity.x = 1.0f;

            // Init transform

            auto &transform = GetComponent<TransformComponent>();

            transform.Translation.x = 0.0f;
            // tc.Translation.y = (float)(std::rand() % 10 - 5);
            transform.Translation.y = 0.0f;
        }

        void OnUpdate(UNUSED(Timestep ts)) {
            auto &sprite = GetComponent<SpriteRendererComponent>();
            auto &anim = GetComponent<AnimationComponent>();

            if (!_Animations[0].IsPlaying) {
                _Animations[0].IsPlaying = true;
                anim = _Animations[0];
                sprite.Texture = anim.Frames[0];
            }
        }

      private:
        static const uint64_t PATAPATA = 90123456789012678;
        glm::vec2 _Pos;
        float clock;
        std::vector<AnimationComponent> _Animations;
    };
}; // namespace Cinematic

#endif /* !Train_HPP_ */
