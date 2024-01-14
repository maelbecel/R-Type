/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef TABROK_HPP_
#define TABROK_HPP_

// Exodia includes
#include "Component/Animation.hpp"
#include "Component/Clock.hpp"
#include "Component/Health.hpp"
#include "Scripts/Enemies/BulletEnemy.hpp"

#include <cmath>
#include <random>

using namespace Exodia;

namespace RType {

    class Tabrok : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t TABROK = 8901235789012345678;
        static const uint64_t DEATH = 183750131800543235;

        const float TimeBetweenAnimations = 9.2f;

        /////////////
        //  enum   //
        /////////////
      public:
        enum class State { ALIVE, DEAD };

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override;
        void OnUpdate(Timestep ts) override;
        void OnCollisionEnter(Entity *entity) override;

      public:
        State GetState() const { return _State; }

      private:
        void Shoot();
        void IsDead();
        void CreateAnimations();
        void UpdateAnimations();

        ////////////////
        // Attributes //
        ////////////////
      private:
        State _State = State::ALIVE;
        State _PreviousState = State::DEAD;
        float _AttackTimer;
        float _AttackCooldown = 5.0f;
        std::vector<AnimationComponent> _Animations;
    };
}; // namespace RType

#endif /* !TABROK_HPP_ */
