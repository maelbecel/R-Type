/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Exodia.hpp"
#include "Tools/ParticleProps.hpp"

namespace FlappyBird {

    class Player : public Exodia::ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override;
        void OnUpdate(Exodia::Timestep ts) override;
        void OnCollisionEnter(Exodia::Entity *entity) override;

        void OnKeyPressed(int keyCode) override;

        bool IsDead() {return _dead;};

      private:
        void Emit(const ParticleProps &particleProps);

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Time;
        float _EnginePower;
        float _Gravity;
        float _SmokeEmitInterval;
        float _SmokeNextEmitTime;
        bool _dead = false;

        ParticleProps _SmokeParticle;
        ParticleProps _EngineParticle;
    };
}; // namespace FlappyBird

#endif /* !PLAYER_HPP_ */
