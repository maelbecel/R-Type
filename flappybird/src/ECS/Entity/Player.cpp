/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Player
*/

#include "Player.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace Exodia;

namespace FlappyBird {

    void Player::CreateAnimations() {
        AnimationComponent anim;

        std::vector<Ref<SubTexture2D>> frames;

        frames.push_back(Exodia::SubTexture2D::CreateFromCoords(PLAYER, {0, 0}, {10, 13}, {1, 1}));

        anim.Frames = frames;
        anim.IsPlaying = false;
        anim.Repeat = false;
        anim.FrameRate = 0.0f;

        _Animations.push_back(anim);
    }

    void Player::OnCreate() {
        HandleEntity.AddComponent<BoxCollider2DComponent>();
        HandleEntity.AddComponent<Clock>();
        // Set Coords
        TransformComponent &tc = GetComponent<TransformComponent>();
        tc.Translation.x = -10.0f;
        tc.Translation.y = 0.0f;

        RigidBody2DComponent &rb = HandleEntity.AddComponent<RigidBody2DComponent>();

        rb.Type = RigidBody2DComponent::BodyType::Dynamic;
        rb.Mass = 0.0f;
        rb.GravityScale = 0.0f;
        rb.Velocity.x = 5.0f;

        _EnginePower = 0.5f;
        _Gravity = 0.5f;
        _SmokeEmitInterval = 0.4f;
        _SmokeNextEmitTime = 0.0f;
        // Smoke Particles
        // _SmokeParticle.Position = {0.0f, 0.0f};
        // _SmokeParticle.Velocity = {-2.0f, 0.0f};
        // _SmokeParticle.VelocityVariation = {4.0f, 2.0f};
        // _SmokeParticle.SizeBegin = 0.35f;
        // _SmokeParticle.SizeEnd = 0.0f;
        // _SmokeParticle.SizeVariation = 0.15f;
        // _SmokeParticle.ColorBegin = {0.8f, 0.8f, 0.8f, 1.0f};
        // _SmokeParticle.ColorEnd = {0.6f, 0.6f, 0.6f, 1.0f};
        // _SmokeParticle.LifeTime = 4.0f;

        // // Engine Particles
        // _EngineParticle.Position = {0.0f, 0.0f};
        // _EngineParticle.Velocity = {-2.0f, 0.0f};
        // _EngineParticle.VelocityVariation = {3.0f, 1.0f};
        // _EngineParticle.SizeBegin = 0.5f;
        // _EngineParticle.SizeEnd = 0.0f;
        // _EngineParticle.SizeVariation = 0.3f;
        // _EngineParticle.ColorBegin = {254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f};
        // _EngineParticle.ColorEnd = {254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f};
        // _EngineParticle.LifeTime = 1.0f;

        CreateAnimations();
    }

    void Player::OnUpdate(Exodia::Timestep ts) {
        Clock &clock = GetComponent<Clock>();
        clock.ElapsedTime += ts;

        // if (Exodia::Input::IsKeyPressed(EXODIA_KEY_SPACE)) {
        //     _Velocity.y += _EnginePower;

        //     if (_Velocity.y > 0.0f)
        //         _Velocity.y += _EnginePower * 2.0f;

        //     // Engine Particles
        //     glm::vec2 emissionPoint = {0.0f, -0.6f};
        //     float rotation = glm::radians(GetRotation());
        //     glm::vec2 rotated =
        //         glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::vec4(emissionPoint, 0.0f, 1.0f);

        //     _EngineParticle.Position = _Position + glm::vec2(rotated.x, rotated.y);
        //     _EngineParticle.Velocity.y = -_Velocity.y * 0.2f - 0.2f;
        //     _ParticleSystem.Emit(_EngineParticle);
        // } else {
        //     _Velocity.y -= _Gravity;
        // }

        // _Velocity.y = glm::clamp(_Velocity.y, -20.0f, 20.0f);
        // _Position += _Velocity * (float)ts;

        // // Smoke Particles
        // if (_Time > _SmokeNextEmitTime) {
        //     _SmokeParticle.Position = _Position;

        //     _ParticleSystem.Emit(_SmokeParticle);

        //     _SmokeNextEmitTime += _SmokeEmitInterval;
        // }
        // _ParticleSystem.OnUpdate(ts);
    }

    void Player::OnKeyPressed(int keycode) {
        GameObject camera_entity = HandleEntity.GetScene()->GetEntityByName("Camera");

        if (!camera_entity.GetEntity())
            return;
        if (keycode == Key::SPACE) {
            RigidBody2DComponent &rb = GetComponent<RigidBody2DComponent>();

            rb.Velocity.y += _EnginePower;

            if (rb.Velocity.y > 0.0f)
                rb.Velocity.y += _EnginePower * 2.0f;
        }
    }

    void Player::OnKeyReleased(int keycode) {
        if (keycode == Key::SPACE) {
            RigidBody2DComponent &rb = GetComponent<RigidBody2DComponent>();

            rb.Velocity.y -= _Gravity;
        }
    };

    const glm::vec3 &Player::GetPosition() {
        TransformComponent &tc = GetComponent<TransformComponent>();

        return tc.Translation;
    }

    float Player::GetRotation() {
        RigidBody2DComponent &rb = GetComponent<RigidBody2DComponent>();

        return rb.Velocity.y * 4.0f - 90.0f;
    }

    uint32_t Player::GetScore() {
        TransformComponent &tc = GetComponent<TransformComponent>();

        return (uint32_t)(tc.Translation.x + 10.0f) / 10.0f;
    }

    void Player::OnCollisionEnter(Entity *entity) {
        ComponentHandle<TagComponent> tag = entity->GetComponent<TagComponent>();

        if (!tag)
            return;
    };

} // namespace FlappyBird