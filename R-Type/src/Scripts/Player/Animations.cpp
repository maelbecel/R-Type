/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player animations
*/

#include "Player.hpp"

using namespace Exodia;

namespace RType {

    void Player::Idle(AnimationComponent ac, SpriteRendererComponent sc)
    {
        if (_PreviousState == State::MOVE_DOWN) {
            EXODIA_TRACE("Player idle from down");
            _PreviousState = State::IDLE;
            _Animations[0].IsPlaying = false;
            _Animations[1].IsPlaying = false;
            _Animations[2].IsPlaying = false;
            _Animations[3].IsPlaying = false;
            _Animations[4].IsPlaying = true;
            _Animations[5].IsPlaying = false;

            ac = _Animations[4];
            sc.Texture = ac.Frames[0];
        } else if (_PreviousState == State::MOVE_UP) {
            EXODIA_TRACE("Player idle from up");
            _PreviousState = State::IDLE;
            _Animations[0].IsPlaying = false;
            _Animations[1].IsPlaying = false;
            _Animations[2].IsPlaying = false;
            _Animations[3].IsPlaying = true;
            _Animations[4].IsPlaying = false;
            _Animations[5].IsPlaying = false;

            ac = _Animations[3];
            sc.Texture = ac.Frames[0];
        }
    };

    void Player::MoveUp(AnimationComponent ac, SpriteRendererComponent sc)
    {
        EXODIA_TRACE("Player move up");
        _PreviousState = State::MOVE_UP;
        _Animations[0].IsPlaying = false;
        _Animations[1].IsPlaying = true;
        _Animations[2].IsPlaying = false;
        _Animations[3].IsPlaying = false;
        _Animations[4].IsPlaying = false;
        _Animations[5].IsPlaying = false;

        ac = _Animations[1];
        sc.Texture = ac.Frames[0];
    }

    void Player::MoveDown(AnimationComponent ac, SpriteRendererComponent sc)
    {
        EXODIA_TRACE("Player move down");
        _PreviousState = State::MOVE_DOWN;
        _Animations[0].IsPlaying = false;
        _Animations[1].IsPlaying = false;
        _Animations[2].IsPlaying = true;
        _Animations[3].IsPlaying = false;
        _Animations[4].IsPlaying = false;
        _Animations[5].IsPlaying = false;

        ac = _Animations[2];
        sc.Texture = ac.Frames[0];
    }

} // namespace RType