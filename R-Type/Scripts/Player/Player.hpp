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
    #include "Scripts/BulletPlayer.hpp"

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
                DEAD
            };

        /////////////
        // Methods //
        /////////////
        public:

            void OnCreate() override
            {
                _State = State::IDLE;
                _AttackTimer = 0.0f;
                _IsAttacking = false;
                _IsCharging = false;

                std::cout << "Player created" << std::endl;
            }

            void OnUpdate(Timestep ts) override;

            void OnKeyPressed(int keycode) override;

            void OnKeyReleased(int keycode) override;

            void CreateBullet(Timestep ts, TransformComponent &tc);

            void OnCollisionEnter(Entity *entity) override;

            ////////////////////////
            // Getters && Setters //
            ////////////////////////
            State GetState() const
            {
                return _State;
            }

            float GetAttackTimer() const
            {
                return _AttackTimer;
            }

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
};

#endif /* !PLAYER_HPP_ */
