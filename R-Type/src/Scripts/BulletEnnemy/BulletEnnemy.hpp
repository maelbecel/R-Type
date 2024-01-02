/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef BULLETENNEMY_HPP_
#define BULLETENNEMY_HPP_

// Exodia includes
#include "Exodia.hpp"
#include "Component/Animation.hpp"

#include <cmath>

using namespace Exodia;

namespace RType {

    class BulletEnnemy : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t BULLET = 1837501318005432356;

        const float TimeBetweenAnimations = 8.0f;

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override;
        void OnUpdate(UNUSED(Timestep ts)) override;
        void OnCollisionEnter(Entity *entity) override;

      public:
        void SetSpeed(float speed) { _Speed = speed; }

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

#endif /* !BULLETENNEMY_HPP_ */
