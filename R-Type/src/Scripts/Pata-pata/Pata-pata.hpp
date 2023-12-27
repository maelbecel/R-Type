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
            void Shoot(ComponentHandle<TransformComponent> transform);
            void SinusoidalMovement(Timestep ts);
            void IsDead();

        ////////////////
        // Attributes //
        ////////////////
        private:
            State _State;
            float _AttackTimer;
    };
}; // namespace Exodia

#endif /* !PATAPATA_HPP_ */
