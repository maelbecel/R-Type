/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef MID_HPP_
#define MID_HPP_

// Exodia includes
#include "Component/Animation.hpp"
#include "Component/Clock.hpp"
#include "Component/Health.hpp"
#include "Scripts/Enemies/BulletEnemy.hpp"

#include <cmath>
#include <random>

using namespace Exodia;

namespace RType {

    class Mid : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t MID = 4567890123456789012;
        static const uint64_t DEATH = 183750131800543235;

        const float TimeBetweenAnimations = 10.2f;

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

#endif /* !MID_HPP_ */
