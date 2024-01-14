/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

// Exodia includes
#include "Component/Animation.hpp"
#include "Component/Clock.hpp"
#include "Component/Health.hpp"
#include "Scripts/Enemies/BulletEnemy.hpp"

#include "PI.hpp"

#include <cmath>
#include <random>

using namespace Exodia;

namespace RType {

    class PowerUp : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t POWERUP = 678901234567890123;
        static const uint64_t DEATH = 183750131800543235;

        const float TimeBetweenAnimations = 10.2f;

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override;
        void OnUpdate(Timestep ts) override;
        void OnKeyPressed(int keycode) override;
        void OnKeyReleased(int keycode) override;
        void OnCollisionEnter(Entity *entity) override;

      private:
        void Shoot();
        void CreateAnimations();

        ////////////////
        // Attributes //
        ////////////////
      private:
        std::vector<AnimationComponent> _Animations;
        bool _IsAttacking = false;
    };
}; // namespace RType

#endif /* !POWERUP_HPP_ */
