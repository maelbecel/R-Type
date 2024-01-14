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
#include "Component/Animation.hpp"

// R-Type Player Tools
#include "Scripts/Player/PlayerState.hpp"

using namespace Exodia;

namespace RType {

    class Player : public ScriptableEntity {

        /////////////
        // Defines //
        /////////////
      private:
        static const uint64_t PLAYER = 12345678901234578;
        static const uint64_t DEATH = 3456789012345678901;

        const float TimeBetweenAnimations = 13.2f;

        //////////////////////////////
        // Constructor & Destructor //
        //////////////////////////////
      public:
        void OnCreate() override;

        /////////////
        // Methods //
        /////////////
      public:
        void OnUpdate(Timestep ts) override;
        void OnKeyPressed(int keycode) override;
        void OnKeyReleased(int keycode) override;

      private:
        void CreateAnimations();

        void UpdatePlayerAttack(Timestep ts);

        void UpdateAnimations();
        void Idle(AnimationComponent &anim, SpriteRendererComponent &sprite);
        void MoveUp(AnimationComponent &anim, SpriteRendererComponent &sprite);
        void MoveDown(AnimationComponent &anim, SpriteRendererComponent &sprite);

        void Shoot();
        void Charge();

        ////////////////////////
        // Getters && Setters //
        ////////////////////////
      public:
        PlayerState GetState() const;
        void SetState(PlayerState state);

        ////////////////
        // Attributes //
        ////////////////
      private:
        PlayerState _State = PlayerState::IDLE;
        PlayerState _PreviousState = PlayerState::MOVE_DOWN;

        float _AttackTimer = 0.0f;

        bool _IsAttacking = false;
        bool _IsCharging = false;
        bool _IsShooting = false;

        std::vector<AnimationComponent> _Animations;
    };
}; // namespace RType

#endif /* !PLAYER_HPP_ */
