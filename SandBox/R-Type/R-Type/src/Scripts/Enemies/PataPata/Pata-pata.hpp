/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef PATAPATA_HPP_
#define PATAPATA_HPP_

// Exodia includes
#include "Component/Animation.hpp"

#include "PI.hpp"

#include <cmath>
#include <random>

using namespace Exodia;

namespace RType {

    class PataPata : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t PATAPATA = 90123456789012678;
        static const uint64_t DEATH = 183750131800543235;

        const float TimeBetweenAnimations = 13.2f;

        /////////////
        //  enum   //
        /////////////
      public:
        enum class State { ALIVE, DEAD };

        //////////////////
        // Constructors //
        //////////////////
      public:
        void OnCreate() override;

        /////////////
        // Methods //
        /////////////
      public:
        void OnUpdate(Timestep ts) override;

      private:
        void CreateAnimations();
        void IsDead();
        void UpdateAnimations();
        void SinusoidalMovement(Timestep ts);
        void Shoot();

        ////////////////
        // Attributes //
        ////////////////
      private:
        State _State = State::ALIVE;
        State _PreviousState = State::DEAD;

        float _AttackTimer = 0.0f;
        float _AttackCooldown = 5.0f;

        std::vector<AnimationComponent> _Animations;
    };
}; // namespace RType

#endif /* !PATAPATA_HPP_ */
