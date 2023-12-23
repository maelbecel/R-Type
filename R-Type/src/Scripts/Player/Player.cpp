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
        bullet->AddComponent<ScriptComponent>().Get().Bind("BulletPlayer");
        bullet->AddComponent<Animation>(0.0f, 2.0f, 1.0f);
        bullet->AddComponent<BoxCollider2DComponent>();
        bullet->AddComponent<ParentComponent>().Get().Parent = GetComponent<IDComponent>().Get().ID;

        auto body_bullet = bullet->AddComponent<RigidBody2DComponent>();
        body_bullet.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_bullet.Get().Mass = 0.0f;
        body_bullet.Get().GravityScale = 0.0f;
        body_bullet.Get().Velocity.x = 0.0f;
        body_bullet.Get().Velocity.y = 0.0f;

        // auto sprite = bullet->AddComponent<SpriteRendererComponent>();
        // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Missile.png");
        // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 0.0f, 0.0f }, { 17.33f, 14.0f }, { 1.0f, 1.0f });
        bullet->AddComponent<CircleRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f});

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

        if (!GetComponent<Health>())
            return;

        if (_State != State::DEAD && GetComponent<Health>().Get().CurrentHealth == 0) {
            EXODIA_INFO("Player is dead");
            auto velocity = GetComponent<RigidBody2DComponent>();
            auto camera_entity = HandleEntity->GetWorld()->GetEntityByTag("Camera");
            // if (!velocity || !camera_entity)
            //     return;
            // velocity.Get().Velocity.x = camera_entity->GetComponent<RigidBody2DComponent>().Get().Velocity.x;
            // velocity.Get().Velocity.y = camera_entity->GetComponent<RigidBody2DComponent>().Get().Velocity.y;

            // auto animation = GetComponent<Animation>();
            // auto sprite = GetComponent<SpriteRendererComponent>();
            // if (!animation || !sprite)
            //     return;

            // if (GetComponent<TransformComponent>())
            //     GetComponent<TransformComponent>().Get().Scale.y = 1.0f;

            // animation.Get().CurrentFrame = 0;
            // animation.Get().MaxFrame = 8;
            // animation.Get().FrameTime = 0.075f;

            // // Set entity sprite
            // // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/HUD.png");
            // // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 0.0f, 0.0f }, { 33.2f, 32.0f }, { 1.0f, 1.0f });
            // // GetComponent<CircleRendererComponent>().Get().Color = glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f};
            // _State = State::DEAD;
        }
        // else if (_State == State::DEAD) {
        //     auto animation = GetComponent<Animation>();
        //     auto sprite = GetComponent<SpriteRendererComponent>();
        //     if (!animation || !sprite)
        //         return;

        //     if (animation.Get().CurrentFrame == animation.Get().MaxFrame - 1) {
        //         EXODIA_INFO("Player is respawn");
        //         GetComponent<Health>().Get().CurrentHealth = 1;
        //         _State = State::IDLE;
        //         animation.Get().CurrentFrame = 2;
        //         animation.Get().MaxFrame = 2;
        //         animation.Get().FrameTime = 0.1f;

        //         if (GetComponent<TransformComponent>())
        //             GetComponent<TransformComponent>().Get().Scale.y = 0.5f;

        //         // Set entity sprite
        //         // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Player.png");
        //         // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 2.0f, 4.0f }, { 33.2f, 17.2f }, { 1.0f, 1.0f });
        //         // GetComponent<CircleRendererComponent>().Get().Color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f};
        //     }
        // }
    };

    void Player::OnKeyPressed(int keycode)
    {
        EXODIA_INFO("Player is pressing {0}", keycode);
        auto transform = GetComponent<TransformComponent>();
        auto velocity = GetComponent<RigidBody2DComponent>();
        auto camera_entity = HandleEntity->GetWorld()->GetEntityByTag("Camera");
        bool block = false;

        if (transform && velocity && camera_entity && _State != State::DEAD) {
            TransformComponent &camera = camera_entity->GetComponent<TransformComponent>().Get();

            if (transform.Get().Translation.x < camera.Translation.x - 9.5f) {
                _State = State::IDLE;
                transform.Get().Translation.x = camera.Translation.x - 9.5f;
                block = true;
            }
            if (transform.Get().Translation.x > camera.Translation.x + 9.5f) {
                _State = State::IDLE;
                transform.Get().Translation.x = camera.Translation.x + 9.5f;
                block = true;
            }
            if (transform.Get().Translation.y < camera.Translation.y - 5.5f) {
                _State = State::IDLE;
                transform.Get().Translation.y = camera.Translation.y - 5.5f;
                block = true;
            }
            if (transform.Get().Translation.y > camera.Translation.y + 5.5f) {
                _State = State::IDLE;
                transform.Get().Translation.y = camera.Translation.y + 5.5f;
                block = true;
            }

            if (!block) {
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