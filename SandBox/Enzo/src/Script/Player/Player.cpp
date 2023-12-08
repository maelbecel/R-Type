/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#include "Player.hpp"

namespace Exodia {

    void Player::CreateBullet(Timestep ts, TransformComponent &tc) {
        EXODIA_INFO("Player attack");

        Entity *bullet = HandleEntity->GetWorld()->CreateNewEntity("Bullet" + std::to_string(HandleEntity->GetWorld()->GetCount()));

        TransformComponent &bullet_tc = bullet->GetComponent<TransformComponent>().Get();
        bullet_tc.Translation.x = tc.Translation.x + 0.7f;
        bullet_tc.Translation.y = tc.Translation.y - 0.05f;
        bullet_tc.Scale.x = 0.5f;
        bullet_tc.Scale.y = 0.5f;
        auto sprite = bullet->AddComponent<SpriteRendererComponent>();
        bullet->AddComponent<ScriptComponent>().Get().Bind<BulletPlayer>();
        bullet->AddComponent<Animation>(0.0f, 2.0f, 1.0f);
        bullet->AddComponent<BoxCollider2DComponent>();
        bullet->AddComponent<ParentComponent>().Get().Parent = GetComponent<IDComponent>().Get().ID;

        Ref<Texture2D> texture = Texture2D::Create("Assets/Textures/Missile.png");
        sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 0.0f }, { 17.33f, 14.0f }, { 1.0f, 1.0f });

        _AttackTimer += ts.GetSeconds();
        _IsAttacking = true;
    }

    void Player::OnUpdate(Timestep ts) {
        auto transform = GetComponent<TransformComponent>();

        if (transform) {
            TransformComponent &tc = transform.Get();

            // Move player with keyboard
            if (Input::IsKeyPressed(Key::A)) {          // Left
                tc.Translation.x -= _Speed * ts;
                _State = State::IDLE;
            } else if (Input::IsKeyPressed(Key::D)) {   // Right
                tc.Translation.x += _Speed * ts;
                _State = State::IDLE;
            }
            if (Input::IsKeyPressed(Key::W)) {          // Up
                tc.Translation.y += _Speed * ts;
                _State = State::MOVE_UP;
            } else if (Input::IsKeyPressed(Key::S)) {   // Down
                tc.Translation.y -= _Speed * ts;
                _State = State::MOVE_DOWN;
            } else if (Input::IsKeyReleased(Key::W) && Input::IsKeyReleased(Key::S)) { // Idle
                _State = State::IDLE;
            }

            // Simple attack
            if (Input::IsKeyPressed(Key::SPACE) && !_IsAttacking) {
                CreateBullet(ts, tc);
            } else if (Input::IsKeyReleased(Key::SPACE) && _IsAttacking) {
                _AttackTimer = 0.0f;
                _IsAttacking = false;
            }

            // Charge attack
            if (Input::IsKeyPressed(Key::Q) && !_IsCharging) {
                EXODIA_INFO("Player is charging");
                _AttackTimer += ts.GetSeconds();
                _IsCharging = true;
            } else if (Input::IsKeyReleased(Key::Q) && _IsCharging) {
                EXODIA_INFO("Player realease charge after {0} seconds", _AttackTimer);
                _AttackTimer = 0.0f;
                _IsCharging = false;
            }
            if (_IsCharging) {
                _AttackTimer += ts.GetSeconds();
            }
        }
    };

    void Player::OnCollisionEnter(Entity *entity) {
        EXODIA_INFO("Collision with {0}", entity->GetComponent<TagComponent>().Get().Tag);
    };
}