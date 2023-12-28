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
#include "Component/Clock.hpp"
#include "Component/Health.hpp"
#include "Scripts/BulletEnnemy/BulletEnnemy.hpp"

#include <cmath>
#include <random>

using namespace Exodia;

namespace RType {

    const double PI = 3.14159265358979323846;

    class PataPata : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
        private:
            static const uint64_t PATAPATA = 90123456789012678;
            static const uint64_t DEATH    = 183750131800543235;

            const float TimeBetweenAnimations = 13.2f;

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
            void SinusoidalMovement(Timestep ts);
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
}; // namespace Exodia

#endif /* !PATAPATA_HPP_ */
