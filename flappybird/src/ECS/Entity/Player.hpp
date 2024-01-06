/*
** EXODIA PROJECT, 2023
** TryAGame
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Exodia.hpp"
#include "Particles/Particles.hpp"

using namespace Exodia;

namespace FlappyBird {

    class Player : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t PLAYER = 14815285158415;

        // Constructor / Destructor (default)
      public:
        Player();
        ~Player() = default;

            /////////////
            // Methods //
            /////////////
          public:
            void OnCreate() override;
            void OnUpdate(Timestep ts) override;
            void OnKeyPressed(int keycode) override;
            void OnKeyReleased(int keycode) override;
            void OnCollisionEnter(Entity *entity) override;

          public:
            void CreateAnimations();

        // Getter
      public:
        const glm::vec2 &GetPosition();
        float GetRotation();
        uint32_t GetScore();

        // Attributes
      private:
        glm::vec2 _Velocity;

        float _EnginePower;
        float _Gravity;

        float _SmokeEmitInterval;
        float _SmokeNextEmitTime;

        ParticleProps _SmokeParticle;
        ParticleProps _EngineParticle;

        ParticlesSystem _ParticleSystem;

        std::vector<AnimationComponent> _Animations;
    };

  };  // namespace FlappyBird

#endif /* !PLAYER_HPP_ */
