/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PlayerController
*/

#ifndef PLAYERCONTROLLER_HPP_
#define PLAYERCONTROLLER_HPP_

#include "Exodia.hpp"
#include "Scripts/Player/PlayerState.hpp"

namespace RType {

    class PlayerController : public Exodia::ScriptableEntity {

        /////////////
        // Methods //
        /////////////
      public:
        void OnUpdate(Exodia::Timestep ts) override;
        void OnKeyPressed(int keycode) override;
        void OnKeyReleased(int keycode) override;
        bool IsAttached() { return _IsAttached; };

        ///////////////////////
        // Getters & Setters //
        ///////////////////////
      private:
        void SetPlayerState(Exodia::GameObject player, PlayerState state);
        PlayerState GetPlayerState();

        ////////////////
        // Attributes //
        ////////////////
      private:
        float _Speed = 5.0f;
        bool _IsAttached = false;
    };
}; // namespace RType

#endif /* !PLAYERCONTROLLER_HPP_ */
