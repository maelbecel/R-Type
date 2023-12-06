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
    #include "BulletPlayer.hpp"

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
                _Speed = 5.0f;
                _State = State::IDLE;
                _AttackTimer = 0.0f;
                _IsAttacking = false;

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
                    } else if (Input::IsKeyPressed(Key::S)) {
                        tc.Translation.y -= _Speed * ts;
                        _State = State::MOVE_DOWN;
                    } else if (Input::IsKeyReleased(Key::W) && Input::IsKeyReleased(Key::S)) {
                        _State = State::IDLE;
                    }
                    if (Input::IsKeyPressed(Key::SPACE) && !_IsAttacking) {
                        EXODIA_INFO("Player attack");
                        Entity *bullet = HandleEntity->GetWorld()->CreateNewEntity("Bullet" + std::to_string(HandleEntity->GetWorld()->GetCount()));

                        auto &bullet_tc = bullet->GetComponent<TransformComponent>().Get();
                        bullet_tc.Translation.x = tc.Translation.x + 0.7f;
                        bullet_tc.Translation.y = tc.Translation.y;
                        bullet_tc.Scale.x = 0.5f;
                        bullet_tc.Scale.y = 0.5f;
                        bullet->AddComponent<SpriteRendererComponent>();
                        bullet->AddComponent<ScriptComponent>().Get().Bind<BulletPlayer>();
                        bullet->AddComponent<Animation>(0.0f, 2.0f, 1.0f);

                        std::cout << "Bullet ID: " << GetComponent<IDComponent>().Get().ID << std::endl;
                        bullet->AddComponent<ParentComponent>().Get().Parent = GetComponent<IDComponent>().Get().ID;

                        auto sprite = bullet->GetComponent<SpriteRendererComponent>();
                        // Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/HUD.png");
                        // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 8.5f }, { 33.25f, 34.0f }, { 1.0f, 1.0f });
                        Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/Missile.png");
                        sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 0.0f }, { 17.33f, 14.0f }, { 1.0f, 1.0f });

                        _AttackTimer += ts.GetSeconds();
                        _IsAttacking = true;
                    } else if (Input::IsKeyReleased(Key::SPACE) && _IsAttacking) {
                        std::cout << "Attack timer: " << _AttackTimer << std::endl;
                        _AttackTimer = 0.0f;
                        _IsAttacking = false;
                    }
                }
            }

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
            float _Speed;
            State _State;
            float _AttackTimer;
            bool _IsAttacking;
    };
};

#endif /* !PLAYER_HPP_ */
