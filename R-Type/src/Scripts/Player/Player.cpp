/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#include "Player.hpp"
#include "Event/TakeDamage.hpp"

using namespace Exodia;

namespace RType {

    void Player::CreateAnimations()
    {
        AnimationComponent idle;
        AnimationComponent moveUp;
        AnimationComponent moveDown;
        AnimationComponent upToIdle;
        AnimationComponent downToIdle;
        AnimationComponent dead;

        std::vector<Ref<SubTexture2D>> framesIdle;
        std::vector<Ref<SubTexture2D>> framesMoveUp;
        std::vector<Ref<SubTexture2D>> framesMoveDown;
        std::vector<Ref<SubTexture2D>> framesUpToIdle;
        std::vector<Ref<SubTexture2D>> framesDownToIdle;
        std::vector<Ref<SubTexture2D>> framesDead;

        // _Animations[0]
        framesIdle.push_back(SubTexture2D::CreateFromCoords(PLAYER, {2.0f, 4.0f}, {33.2f, 17.2f}, {1.0f, 1.0f}));

        // _Animations[1]
        for (uint32_t x = 3; x < 5; x++)
            framesMoveUp.push_back(SubTexture2D::CreateFromCoords(PLAYER, {x, 4.0f}, {33.2f, 17.2f}, {1.0f, 1.0f}));

        // _Animations[2]
        for (int32_t x = 1; x > -1; x--)
            framesMoveDown.push_back(SubTexture2D::CreateFromCoords(PLAYER, {x, 4.0f}, {33.2f, 17.2f}, {1.0f, 1.0f}));

        // _Animations[3]
        for (uint32_t x = 1; x < 3; x++)
            framesDownToIdle.push_back(SubTexture2D::CreateFromCoords(PLAYER, {x, 4.0f}, {33.2f, 17.2f}, {1.0f, 1.0f}));

        // _Animations[4]
        for (int32_t x = 3; x > 1; x--)
            framesUpToIdle.push_back(SubTexture2D::CreateFromCoords(PLAYER, {x, 4.0f}, {33.2f, 17.2f}, {1.0f, 1.0f}));

        // _Animations[5]
        for (uint32_t x = 0; x < 8; x++)
            framesDead.push_back(SubTexture2D::CreateFromCoords(DEATH, {x, 0.0f}, {33.2f, 32.0f}, {1.0f, 1.0f}));

        idle.Frames = framesIdle;
        idle.IsPlaying = false;
        idle.Repeat = false;
        idle.FrameRate = TimeBetweenAnimations;

        moveUp.Frames = framesMoveUp;
        moveUp.IsPlaying = false;
        moveUp.Repeat = false;
        moveUp.FrameRate = TimeBetweenAnimations;

        moveDown.Frames = framesMoveDown;
        moveDown.IsPlaying = false;
        moveDown.Repeat = false;
        moveDown.FrameRate = TimeBetweenAnimations;

        upToIdle.Frames = framesUpToIdle;
        upToIdle.IsPlaying = false;
        upToIdle.Repeat = false;
        upToIdle.FrameRate = TimeBetweenAnimations;

        downToIdle.Frames = framesDownToIdle;
        downToIdle.IsPlaying = false;
        downToIdle.Repeat = false;
        downToIdle.FrameRate = TimeBetweenAnimations;

        dead.Frames = framesDead;
        dead.IsPlaying = false;
        dead.Repeat = false;
        dead.FrameRate = TimeBetweenAnimations;

        _Animations.push_back(idle);
        _Animations.push_back(moveUp);
        _Animations.push_back(moveDown);
        _Animations.push_back(upToIdle);
        _Animations.push_back(downToIdle);
        _Animations.push_back(dead);
    }

    void Player::OnCreate()
    {
        HandleEntity.AddComponent<Health>(1);
        HandleEntity.AddComponent<BoxCollider2DComponent>();

        TransformComponent &tc = GetComponent<TransformComponent>();

        tc.Scale.y = 0.5f;
        tc.Translation.y = 0.4f;

        // Set entity rigidbody
        RigidBody2DComponent &rb = HandleEntity.AddComponent<RigidBody2DComponent>();

        rb.Type         = RigidBody2DComponent::BodyType::Dynamic;
        rb.Mass         = 0.0f;
        rb.GravityScale = 0.0f;
        rb.Velocity     = glm::vec2{0.0f, 0.0f};

        // Set entity animations
        CreateAnimations();
    }

    void Player::Shoot(TransformComponent &tc)
    {
        EXODIA_INFO("Player attack");

        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject bullet = scene->CreateNewEntity("Bullet" + std::to_string(scene->GetWorldPtr()->GetCount()));

        bullet.AddComponent<ParentComponent>().Parent = GetComponent<IDComponent>().ID;
        bullet.AddComponent<ScriptComponent>().Bind("BulletPlayer");

        _IsAttacking = true;
    }

    void Player::UpdateAnimations()
    {
        SpriteRendererComponent &sprite = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = GetComponent<AnimationComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;

            anim = HandleEntity.AddComponent<AnimationComponent>(_Animations[0]);

            sprite.Texture = anim.Frames[0];
        } else {
            if (_State == State::IDLE && _PreviousState != State::IDLE) {
                Idle(anim, sprite);
            } else if (_State == State::MOVE_UP && _PreviousState != State::MOVE_UP) {
                MoveUp(anim, sprite);
            } else if (_State == State::MOVE_DOWN && _PreviousState != State::MOVE_DOWN) {
                MoveDown(anim, sprite);
            }
        }
    }

    void Player::OnUpdate(Timestep ts)
    {
        TransformComponent &tc = GetComponent<TransformComponent>();
        Health             &h  = GetComponent<Health>();

        if (_IsCharging) {
            _AttackTimer += ts.GetSeconds();
        } else if (_IsShooting) {
            _AttackTimer += ts.GetSeconds();

            _IsShooting = false;
        }

        UpdateAnimations();

        if (_State != State::DEAD && h.CurrentHealth <= 0) {
            EXODIA_INFO("Player is dead");

            RigidBody2DComponent &rbc = GetComponent<RigidBody2DComponent>();
            Scene *scene = HandleEntity.GetScene();

            if (!scene)
                return;

            GameObject camera_entity         = scene->GetEntityByName("Camera");
            RigidBody2DComponent &camera_rbc = camera_entity.GetComponent<RigidBody2DComponent>();

            rbc.Velocity.x = camera_rbc.Velocity.x;
            rbc.Velocity.y = camera_rbc.Velocity.y;

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
            // 3456789012345678901
            // // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/HUD.png");
            // // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 0.0f, 0.0f }, { 33.2f, 32.0f
            // }, { 1.0f, 1.0f });
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
        //         // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 2.0f, 4.0f },
        //         { 33.2f, 17.2f }, { 1.0f, 1.0f });
        //         // GetComponent<CircleRendererComponent>().Get().Color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f};
        //     }
        // }
    };

    void Player::OnKeyPressed(int keycode) {
        auto &transform = GetComponent<TransformComponent>();
        auto &velocity  = GetComponent<RigidBody2DComponent>();

        auto *camera_entity = HandleEntity.GetScene()->GetEntityByName("Camera");

        bool block = false;

        if (!camera_entity)
            return;

        if (_State != State::DEAD) {
            TransformComponent &camera = camera_entity->GetComponent<TransformComponent>().Get();

            /*
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
            */

            if (!block) {
                // Move player with keyboard
                if (keycode == Key::A) { // Left
                    velocity.Velocity.x = -5.0f;
                } else if (keycode == Key::D) { // Right
                    velocity.Velocity.x = 5.0f;
                }

                if (keycode == Key::W) { // Up
                    _State = State::MOVE_UP;
                    velocity.Velocity.y = 5.0f;
                } else if (keycode == Key::S) { // Down
                    _State = State::MOVE_DOWN;
                    velocity.Velocity.y = -5.0f;
                }
            }

            // Simple attack
            if (keycode == Key::SPACE && !_IsAttacking) {
                Shoot(GetComponent<TransformComponent>());
            }

            // Charge attack
            if (keycode == Key::Q && !_IsCharging) {
                _IsCharging = true;
            }
        }
    };

    void Player::OnKeyReleased(int keycode)
    {
        auto &velocity = GetComponent<RigidBody2DComponent>();

        if (keycode == Key::A || keycode == Key::D) {
            velocity.Velocity.x = 0.0f;
        }
        if (keycode == Key::W || keycode == Key::S) {
            _State = State::IDLE;
            velocity.Velocity.y = 0.0f;
        }

        if (keycode == Key::SPACE && _IsAttacking) {
            _AttackTimer = 0.0f;
            _IsAttacking = false;
        }

        if (keycode == Key::Q && _IsCharging) {
            EXODIA_TRACE("Player realease charge after {0} seconds", _AttackTimer);

            _AttackTimer = 0.0f;
            _IsCharging = false;
        }
    }

    void Player::OnCollisionEnter(Entity *entity)
    {
        Health &player_health = GetComponent<Health>();
        ComponentHandle<TagComponent> tag = entity->GetComponent<TagComponent>();

        if (!tag)
            return;

        TagComponent &player_tag = GetComponent<TagComponent>();

        if (player_tag.Tag.rfind("BE", 0) == 0) {
            EXODIA_INFO("BE {0} hit", player_tag.Tag);

            HandleEntity.GetScene()->GetWorldPtr()->Emit<Events::TakeDamage>({HandleEntity, 1});
        }
    };
}; // namespace RType
