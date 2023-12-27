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
        State _State;
        float _AttackTimer;
        bool _IsAttacking;
        bool _IsCharging;
        bool _IsShooting = false;
    };
}; // namespace RType

#endif /* !PLAYER_HPP_ */
