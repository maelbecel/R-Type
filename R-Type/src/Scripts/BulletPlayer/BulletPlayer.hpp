/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef BULLETPLAYER_HPP_
#define BULLETPLAYER_HPP_

// Exodia includes
#include "Component/Animation.hpp"

#include <cmath>

using namespace Exodia;

namespace RType {

    class BulletPlayer : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t BULLET = 18375012605620;
        const float TimeBetweenAnimations = 8.0f;

        /////////////
        // Methods //
        /////////////
      public:
        void OnCreate() override;
        void OnUpdate(UNUSED(Timestep ts)) override;
        void OnCollisionEnter(Entity *entity) override;

      private:
        void CreateAnimations();
        void UpdateAnimations();

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Speed = 15.0f;
        std::vector<AnimationComponent> _Animations;
        bool _NeedUpdate = true;
    };
}; // namespace RType

#endif /* !BULLETPLAYER_HPP_ */
