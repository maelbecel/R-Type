/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Player
*/

#include "Player.hpp"
#include "Tools/Random.hpp"

using namespace Exodia;

namespace FlappyBird {

    /////////////
    // Methods //
    /////////////

    /**
     * The function initializes the properties of the player's smoke and engine particles.
     */
    void Player::OnCreate() {
        _Time = 0.0f;
        _EnginePower = 1.0f;
        _SmokeEmitInterval = 0.4f;
        _SmokeNextEmitTime = 0.4f;

        // Smoke Particles
        _SmokeParticle.Position = {0.0f, 0.0f};
        _SmokeParticle.Velocity = {-2.0f, 0.0f};
        _SmokeParticle.VelocityVariation = {4.0f, 2.0f};
        _SmokeParticle.SizeBegin = 0.35f;
        _SmokeParticle.SizeEnd = 0.0f;
        _SmokeParticle.SizeVariation = 0.15f;
        _SmokeParticle.ColorBegin = {0.8f, 0.8f, 0.8f, 1.0f};
        _SmokeParticle.ColorEnd = {0.6f, 0.6f, 0.6f, 1.0f};
        _SmokeParticle.LifeTime = 1.0f;
        _SmokeParticle.NumberOfParticles = 2;

        // Engine Particles
        _EngineParticle.Position = {0.0f, 0.0f};
        _EngineParticle.Velocity = {-2.0f, 0.0f};
        _EngineParticle.VelocityVariation = {3.0f, 1.0f};
        _EngineParticle.SizeBegin = 0.5f;
        _EngineParticle.SizeEnd = 0.0f;
        _EngineParticle.SizeVariation = 0.3f;
        _EngineParticle.ColorBegin = {254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f};
        _EngineParticle.ColorEnd = {254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f};
        _EngineParticle.LifeTime = 1.0f;
        _EngineParticle.NumberOfParticles = 10;
    }

    /**
     * The function updates the player's position, emits smoke particles, rotates the player based on
     * velocity, and destroys the player if it goes out of bounds.
     *
     * @param ts Timestep is a time interval that represents the elapsed time since the last frame
     * update. It is used to control the timing of various game events and animations.
     */
    void Player::OnUpdate(Timestep ts) {
        _Time += ts;

        // Smoke Particles
        if (_Time > _SmokeNextEmitTime) {
            _SmokeParticle.Position = {GetComponent<TransformComponent>().Translation.x,
                                       GetComponent<TransformComponent>().Translation.y};

            Emit(_SmokeParticle);

            _SmokeNextEmitTime += _SmokeEmitInterval;
        }

        TransformComponent &tc = GetComponent<TransformComponent>();
        RigidBody2DComponent &rbc = GetComponent<RigidBody2DComponent>();

        tc.Rotation.z = rbc.Velocity.y * 0.1f;

        auto &pos = GetComponent<TransformComponent>().Translation;

        if (pos.y < -10.0f || pos.y > 10.0f)
            HandleEntity.GetScene()->DestroyEntity(HandleEntity);
    }

    /**
     * The OnCollisionEnter function logs a collision with an entity and sets the player's "dead" flag
     * to true, then destroys the entity.
     *
     * @param entity The "entity" parameter is a pointer to an instance of the Exodia::Entity class.
     */
    void Player::OnCollisionEnter(UNUSED(Exodia::Entity *entity)) {
        _dead = true;

        HandleEntity.GetScene()->DestroyEntity(HandleEntity);
    }

    /**
     * The function `OnKeyPressed` increases the velocity of the player's rigid body and emits engine
     * particles when the space key is pressed.
     *
     * @param keyCode The `keyCode` parameter represents the key code of the key that was pressed. It
     * is used to check if the SPACE key was pressed.
     */
    void Player::OnKeyPressed(int keyCode) {
        if (keyCode == Key::SPACE) {
            RigidBody2DComponent &rbc = GetComponent<RigidBody2DComponent>();
            TransformComponent &tc = GetComponent<TransformComponent>();

            rbc.Velocity.y += _EnginePower;

            if (rbc.Velocity.y > 0.0f)
                rbc.Velocity.y += _EnginePower * 2.0f;

            // Engine Particles
            glm::vec2 emissionPoint = {0.0f, -0.6f};
            float rotation = glm::radians(tc.Rotation.z);
            glm::vec2 rotated =
                glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::vec4(emissionPoint, 0.0f, 1.0f);

            _EngineParticle.Position = glm::vec2(tc.Translation.x, tc.Translation.y) + glm::vec2(rotated.x, rotated.y);
            _EngineParticle.Velocity.y = -rbc.Velocity.y * 0.2f - 0.2f;

            Emit(_EngineParticle);
        }
    }

    /**
     * The function emits a specified number of particles with various properties such as position,
     * rotation, size, color, lifetime, velocity, and gravity.
     *
     * @param props The "props" parameter is of type "ParticleProps", which is a user-defined struct or
     * class that contains properties for creating particles. It likely includes information such as
     * the number of particles to create, the position of the particles, their size, color, lifetime,
     * velocity, and other relevant attributes.
     */
    void Player::Emit(const ParticleProps &props) {
        for (int i = 0; i < props.NumberOfParticles; i++) {
            GameObject particle = HandleEntity.GetScene()->CreateNewEntity("Particle #" + std::to_string(i));

            TransformComponent &tc = particle.GetComponent<TransformComponent>();

            tc.Translation.x = props.Position.x;
            tc.Translation.y = props.Position.y;
            tc.Rotation.z = Random::Float();
            tc.Scale = glm::vec3(props.SizeBegin + props.SizeVariation * (Random::Float() - 0.5f));

            SpriteRendererComponent &src = particle.AddComponent<SpriteRendererComponent>();

            src.Color = props.ColorBegin;

            ParticleComponent &pc = particle.AddComponent<ParticleComponent>();

            pc.LifeTime = props.LifeTime;
            pc.LifeRemaining = props.LifeTime;
            pc.ColorBegin = props.ColorBegin;
            pc.ColorEnd = props.ColorEnd;
            pc.SizeBegin = props.SizeBegin + props.SizeVariation * (Random::Float() - 0.5f);
            pc.SizeEnd = props.SizeEnd;

            RigidBody2DComponent &rbc = particle.AddComponent<RigidBody2DComponent>();

            rbc.Type = RigidBody2DComponent::BodyType::Dynamic;
            rbc.Velocity = props.Velocity;
            rbc.Velocity.x += props.VelocityVariation.x * (Random::Float() - 0.5f);
            rbc.Velocity.y += props.VelocityVariation.y * (Random::Float() - 0.5f);
            rbc.GravityScale = 0.0f;
            rbc.Mass = 0.0f;
        }
    }
}; // namespace FlappyBird
