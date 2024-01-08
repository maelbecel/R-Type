/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Particle
*/

#ifndef PARTICLE_HPP_
    #define PARTICLE_HPP_

    // Exodia includes
    #include "Exodia.hpp"

namespace RType {

    using namespace Exodia;

    class ParticleController : public ScriptableEntity {

        ////////////////
        // Structures //
        ////////////////
        public:

            struct ParticleProps {
                glm::vec2 Position;
                glm::vec2 Velocity;
                glm::vec2 VelocityVariation;
                glm::vec4 ColorBegin;
                glm::vec4 ColorEnd;
                float SizeBegin;
                float SizeEnd;
                float SizeVariation;
                float LifeTime = 1.0f;

                int NumParticles = 1;
            };

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override
            {
                // Smoke Particles
                _SmokeParticle.Position = {  0.0f, 0.0f };
                _SmokeParticle.Velocity = { -2.0f, 0.0f };
                _SmokeParticle.VelocityVariation = { 4.0f, 2.0f };
                _SmokeParticle.SizeBegin = 0.35f;
                _SmokeParticle.SizeEnd = 0.0f;
                _SmokeParticle.SizeVariation = 0.15f;
                _SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
                _SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
                _SmokeParticle.LifeTime = 4.0f;

                // Engine Particles
                _EngineParticle.Position = {  0.0f, 0.0f };
                _EngineParticle.Velocity = { -2.0f, 0.0f };
                _EngineParticle.VelocityVariation = { 3.0f, 1.0f };
                _EngineParticle.SizeBegin = 0.5f;
                _EngineParticle.SizeEnd = 0.0f;
                _EngineParticle.SizeVariation = 0.3f;
                _EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
                _EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
                _EngineParticle.LifeTime = 1.0f;
                _EngineParticle.NumParticles = 999;
            }

            void OnUpdate(Timestep ts) override
            {
                _Time += ts;

                if (_Time > _SmokeNextEmitTime) {
                    Emit(_SmokeParticle);

                    _SmokeNextEmitTime += _SmokeEmitInterval;
                }
            }

            void OnKeyPressed(int keycode) override
            {
                if (keycode == Key::SPACE) {
                    glm::vec2 mousePos = Input::GetMousePosition();

                    _EngineParticle.Position   = mousePos;

                    Emit(_EngineParticle);
                }
            }

        private:

            void Emit(ParticleProps &props)
            {
                std::mt19937 engine;
                std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

                for (int i = 0; i < props.NumParticles; i++) {
                    GameObject particle = HandleEntity.GetScene()->CreateNewEntity("Particle #" + std::to_string(i));

                    TransformComponent &tc = particle.GetComponent<TransformComponent>();

                    tc.Translation.x = props.Position.x + Input::GetMousePosition().x;
                    tc.Translation.y = props.Position.y + Input::GetMousePosition().y;
                    tc.Rotation.z = (float)distribution(engine);
                    tc.Scale = glm::vec3(props.SizeBegin + props.SizeVariation * ((float)distribution(engine) - 0.5f));

                    SpriteRendererComponent &src = particle.AddComponent<SpriteRendererComponent>();

                    src.Color = props.ColorBegin;

                    ParticleComponent &pc = particle.AddComponent<ParticleComponent>();

                    pc.LifeTime      = props.LifeTime;
                    pc.LifeRemaining = props.LifeTime;
                    pc.ColorBegin    = props.ColorBegin;
                    pc.ColorEnd      = props.ColorEnd;
                    pc.SizeBegin     = props.SizeBegin + props.SizeVariation * ((float)distribution(engine) - 0.5f);
                    pc.SizeEnd       = props.SizeEnd;

                    RigidBody2DComponent &rbc = particle.AddComponent<RigidBody2DComponent>();

                    rbc.Type = RigidBody2DComponent::BodyType::Dynamic;
                    rbc.Velocity = props.Velocity;
                    rbc.Velocity.x += props.VelocityVariation.x * ((float)distribution(engine) - 0.5f);
                    rbc.Velocity.y += props.VelocityVariation.y * ((float)distribution(engine) - 0.5f);
                    rbc.GravityScale = 0.0f;
                    rbc.Mass = 0.0f;
                }
            }

        ///////////////
        // Atributes //
        ///////////////
        private:

            ParticleProps _SmokeParticle;
            ParticleProps _EngineParticle;

            float _Time;
            float _SmokeEmitInterval;
            float _SmokeNextEmitTime;
    };
};

#endif /* !PARTICLE_HPP_ */
