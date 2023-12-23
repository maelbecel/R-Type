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
        bullet->AddComponent<ScriptComponent>().Get().Bind<BulletPlayer>();
        bullet->AddComponent<Animation>(0.0f, 2.0f, 1.0f);
        bullet->AddComponent<BoxCollider2DComponent>();
        bullet->AddComponent<ParentComponent>().Get().Parent = GetComponent<IDComponent>().Get().ID;

        // auto sprite = bullet->AddComponent<SpriteRendererComponent>();
        // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Missile.png");
        // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 0.0f, 0.0f }, { 17.33f, 14.0f }, { 1.0f, 1.0f });

        _AttackTimer += ts.GetSeconds();
        _IsAttacking = true;
    }

    void Player::OnUpdate(Timestep ts) {
        if (_IsCharging) {
            _AttackTimer += ts.GetSeconds();
        }
        if (_IsShooting) {
            CreateBullet(ts, GetComponent<TransformComponent>().Get());
            _IsShooting = false;
        }
    };

    void Player::OnKeyPressed(int keycode)
    {
        EXODIA_INFO("Player is pressing {0}", keycode);
        auto transform = GetComponent<TransformComponent>();
        auto velocity = GetComponent<RigidBody2DComponent>();

        if (transform && velocity) {
            // Move player with keyboard
            if (keycode == Key::A) {          // Left
                EXODIA_INFO("Player is moving left");
                _State = State::IDLE;
                velocity.Get().Velocity.x = -5.0f;
            } else if (keycode == Key::D) {   // Right
                EXODIA_INFO("Player is moving right");
                _State = State::IDLE;
                velocity.Get().Velocity.x = 5.0f;
            }

            if (keycode == Key::W) {          // Up
                EXODIA_INFO("Player is moving up");
                _State = State::MOVE_UP;
                velocity.Get().Velocity.y = 5.0f;
            } else if (keycode == Key::S) {   // Down
                EXODIA_INFO("Player is moving down");
                _State = State::MOVE_DOWN;
                velocity.Get().Velocity.y = -5.0f;
            }

            // Simple attack
            if (keycode == Key::SPACE && !_IsAttacking) {
                EXODIA_INFO("Player is shooting");
                _IsShooting = true;
            }

            // Charge attack
            if (keycode == Key::Q && !_IsCharging) {
                EXODIA_INFO("Player is charging");
                _IsCharging = true;
            }
        }
    };

    void Player::OnKeyReleased(int keycode)
    {
        auto velocity = GetComponent<RigidBody2DComponent>();

        if (velocity) {
            if (keycode == Key::A || keycode == Key::D) {
                _State = State::IDLE;
                velocity.Get().Velocity.x = 0.0f;
            }
            if (keycode == Key::W || keycode == Key::S) {
                _State = State::IDLE;
                velocity.Get().Velocity.y = 0.0f;
            }

            if (keycode == Key::SPACE && _IsAttacking) {
                _AttackTimer = 0.0f;
                _IsAttacking = false;
            }

            if (keycode == Key::Q && _IsCharging) {
                EXODIA_INFO("Player realease charge after {0} seconds", _AttackTimer);
                _AttackTimer = 0.0f;
                _IsCharging = false;
            }
        }
    }


    void Player::OnCollisionEnter(Entity *entity) {
        if (entity->GetComponent<TagComponent>().Get().Tag.rfind("BE", 0) == 0) {
            EXODIA_INFO("BE {0} hit", entity->GetComponent<TagComponent>().Get().Tag);
            entity->GetWorld()->DestroyEntity(entity);
            GetComponent<Health>().Get().CurrentHealth -= 1;
            EXODIA_INFO("Player health: {0}", GetComponent<Health>().Get().CurrentHealth);
        }
    };
}