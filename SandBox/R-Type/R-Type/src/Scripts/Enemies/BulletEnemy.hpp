/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef BULLETENEMY_HPP_
#define BULLETENEMY_HPP_

// Exodia includes
#include "Exodia.hpp"
#include "Component/Animation.hpp"
#include "Component/Clock.hpp"

#include <cmath>

using namespace Exodia;

namespace RType {

    class BulletEnemy : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t BULLET = 1837501318005432356;

        const float TimeBetweenAnimations = 8.0f;

        /////////////////
        // Constructor //
        /////////////////
      public:
        void OnCreate() override;

        /////////////
        // Methods //
        /////////////
      public:
        void OnUpdate(Timestep ts) override;
        void OnCollisionEnter(Entity *entity) override;

      private:
        void CreateAnimations();
        void UpdateAnimations();

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Speed = 10.0f;
        std::vector<AnimationComponent> _Animations;
        bool _IsColliding = false;
    };
}; // namespace RType

#endif /* !BULLETENEMY_HPP_ */
