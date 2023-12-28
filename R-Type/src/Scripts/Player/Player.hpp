/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

// Exodia includes
#include "Exodia.hpp"
#include "Scripts/BulletPlayer/BulletPlayer.hpp"
#include "Component/Health.hpp"

using namespace Exodia;

namespace RType {

    class Player : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
        private:

            static const uint64_t PLAYER  = 12345678901234578;
            static const uint64_t DEATH   = 3456789012345678901;

            const float TimeBetweenAnimations = 5.0f;

        //////////////
        //  Enums   //
        //////////////
      public:
        enum class State { IDLE = 0, MOVE_UP, MOVE_DOWN, DEAD };

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
        void Shoot(Timestep ts, TransformComponent &tc);
        void CreateAnimations();
        void UpdateAnimations();

      private:
        void Idle(AnimationComponent anim, SpriteRendererComponent sprite);
        void MoveUp(AnimationComponent anim, SpriteRendererComponent sprite);
        void MoveDown(AnimationComponent anim, SpriteRendererComponent sprite);

        ////////////////////////
        // Getters && Setters //
        ////////////////////////
      public:
        State GetState() const { return _State; }
        float GetAttackTimer() const { return _AttackTimer; }

        ////////////////
        // Attributes //
        ////////////////
      private:

        State _State = State::IDLE;
        State _PreviousState = State::MOVE_DOWN;
        float _AttackTimer = 0.0f;
        bool _IsAttacking = false;
        bool _IsCharging = false;
        bool _IsShooting = false;
        std::vector<AnimationComponent> _Animations;
    };
}; // namespace RType

#endif /* !PLAYER_HPP_ */
