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

namespace Exodia {

    class Player : public ScriptableEntity {

        //////////////
        //  Enums   //
        //////////////
        public:
            enum class State {
                IDLE = 0,
                MOVE_UP,
                MOVE_DOWN,
                ATTACK,
                CHARGE,
                DEAD
            };

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override
            {
                _Speed = 5.0f;
                _State = State::IDLE;

                std::cout << "Player created" << std::endl;
            }

            void OnUpdate(Timestep ts) override
            {
                auto transform = GetComponent<TransformComponent>();

                if (transform) {
                    auto &tc = transform.Get();

                    if (Input::IsKeyPressed(Key::A)) {
                        tc.Translation.x -= _Speed * ts;
                        _State = State::IDLE;
                    }
                    if (Input::IsKeyPressed(Key::D)) {
                        tc.Translation.x += _Speed * ts;
                        _State = State::IDLE;
                    }
                    if (Input::IsKeyPressed(Key::W)) {
                        tc.Translation.y += _Speed * ts;
                        _State = State::MOVE_UP;
                    }
                    if (Input::IsKeyPressed(Key::S)) {
                        tc.Translation.y -= _Speed * ts;
                        _State = State::MOVE_DOWN;
                    }
                    // if (Input::IsKeyReleased(Key::Unknown)) {
                    //     std::cout << "Unknown key pressed" << std::endl;
                    //     _State = State::IDLE;
                    // }
                }
            }

            State GetState() const
            {
                return _State;
            }

        ////////////////
        // Attributes //
        ////////////////
        private:
            float _Speed;
            State _State;
    };
};

#endif /* !PLAYER_HPP_ */
