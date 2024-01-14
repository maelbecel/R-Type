/*
** EPITECH PROJECT, 2023
** $
** File description:
** Player
*/

#include "Player.hpp"
#include "Component/Health.hpp"
#include "Scripts/Player/PlayerController.hpp"

using namespace Exodia;

namespace RType {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    void Player::OnCreate() {
        // -- Instantiate player animations
        CreateAnimations();

        // -- Generate a random color for the player
        /*std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.3f, 1.0f);

        GetComponent<SpriteRendererComponent>().Color = {dis(gen), dis(gen), dis(gen), 1.0f};*/
    }

    void Player::CreateAnimations() {
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

    void Player::OnUpdate(Timestep ts) {
        // -- Handle Player Attack
        if (_State != PlayerState::DEAD)
            UpdatePlayerAttack(ts);

        UpdateAnimations();

        if (_State == PlayerState::DEAD)
            return;

        TransformComponent &tc = GetComponent<TransformComponent>();
        Health &health = GetComponent<Health>();

        // -- If player not currently dead and health is 0
        if (_State != PlayerState::DEAD && health.CurrentHealth <= 0) {
            Scene *scene = HandleEntity.GetScene();

            if (scene) {
                GameObject cameraObject = scene->GetPrimaryCamera();

                if (cameraObject.GetEntity() && cameraObject.HasComponent<RigidBody2DComponent>()) {
                    auto &cameraRBC = cameraObject.GetComponent<RigidBody2DComponent>();
                    auto &playerRBC = GetComponent<RigidBody2DComponent>();

                    playerRBC.Velocity.x = cameraRBC.Velocity.x;
                    playerRBC.Velocity.y = cameraRBC.Velocity.y;
                }
            }

            SetState(PlayerState::DEAD);

            // TODO: Do Death Animation, at the end of the animation, destroy the player
            EXODIA_TRACE("Player '{0}' is dead. Welcome in spectator mode.", GetComponent<TagComponent>().Tag);
        }
    }

    void Player::OnKeyPressed(int keycode) {
        if (_State == PlayerState::DEAD)
            return;

        // -- Simple Attack
        if (keycode == Key::SPACE && !_IsAttacking) {
            if (!HandleEntity.HasComponent<ParentComponent>())
                return;
            auto &pc = HandleEntity.GetComponent<ParentComponent>();
            auto parent = HandleEntity.GetScene()->GetEntityByUUID(pc.Parent);

            if (!parent.GetEntity())
                return;
            auto script = parent.GetEntity()->GetComponent<ScriptComponent>();

            if (!script)
                return;
            auto &sc = script.Get();

            if (sc.Name == "PlayerController" && sc.Instance) {
                auto *player = dynamic_cast<PlayerController *>(sc.Instance);

                if (player && player->IsAttached()) {
                    return;
                }
            }
            Shoot();
        }

        // -- Charged Attack
        if (keycode == Key::Q && !_IsCharging)
            _IsCharging = true;
    }

    void Player::OnKeyReleased(int keycode) {
        if (_State == PlayerState::DEAD)
            return;
        if (keycode == Key::SPACE && _IsAttacking) {
            _AttackTimer = 0.0f;
            _IsAttacking = false;
        }

        if (keycode == Key::Q && _IsCharging) {
            Charge();
        }
    }

    void Player::UpdatePlayerAttack(Timestep ts) {
        if (_IsCharging)
            _AttackTimer += ts.GetSeconds();
        else if (_IsShooting) {
            _AttackTimer += ts.GetSeconds();

            _IsShooting = false;
        }
    }

    void Player::UpdateAnimations() {
        SpriteRendererComponent &sprite = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = HandleEntity.GetEntity()->GetComponent<AnimationComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;

            anim = HandleEntity.GetEntity()->AddComponent<AnimationComponent>(_Animations[0]);

            sprite.Texture = anim.Get().Frames[0];
        } else {
            auto &animation = anim.Get();

            if (_State == PlayerState::IDLE && _PreviousState != PlayerState::IDLE)
                Idle(animation, sprite);
            else if (_State == PlayerState::MOVE_UP && _PreviousState != PlayerState::MOVE_UP)
                MoveUp(animation, sprite);
            else if (_State == PlayerState::MOVE_DOWN && _PreviousState != PlayerState::MOVE_DOWN)
                MoveDown(animation, sprite);
            // TODO: Update the death animation
        }
    }

    void Player::Idle(AnimationComponent &animation, SpriteRendererComponent &sprite) {
        if (_PreviousState == PlayerState::MOVE_DOWN) {
            _PreviousState = PlayerState::IDLE;

            for (int i = 0; i < 6; i++)
                _Animations[i].IsPlaying = false;
            _Animations[4].IsPlaying = true;

            animation = _Animations[4];
            sprite.Texture = animation.Frames[0];
        } else if (_PreviousState == PlayerState::MOVE_UP) {
            _PreviousState = PlayerState::IDLE;

            for (int i = 0; i < 6; i++)
                _Animations[i].IsPlaying = false;
            _Animations[3].IsPlaying = true;

            animation = _Animations[3];
            sprite.Texture = animation.Frames[0];
        }
    }

    void Player::MoveUp(AnimationComponent &animation, SpriteRendererComponent &sprite) {
        _PreviousState = PlayerState::MOVE_UP;

        for (int i = 0; i < 6; i++)
            _Animations[i].IsPlaying = false;
        _Animations[1].IsPlaying = true;

        animation = _Animations[1];
        sprite.Texture = animation.Frames[0];
    }

    void Player::MoveDown(AnimationComponent &animation, SpriteRendererComponent &sprite) {
        _PreviousState = PlayerState::MOVE_DOWN;

        for (int i = 0; i < 6; i++)
            _Animations[i].IsPlaying = false;
        _Animations[2].IsPlaying = true;

        animation = _Animations[2];
        sprite.Texture = animation.Frames[0];
    }

    void Player::Shoot() {
        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject bullet = scene->LoadPrefabs(
            (Project::GetActiveAssetDirectory() / "Prefabs/Bullets/BulletPlayer.prefab").string(), true);

        bullet.GetComponent<TagComponent>().Tag = "BP";
        auto &bulletID = bullet.GetComponent<IDComponent>();

        // bulletID.ID = UUID();

        bullet.AddComponent<ParentComponent>().Parent = GetComponent<IDComponent>().ID;
        GetComponent<ChildrenComponent>().Children.push_back(bulletID.ID);

        auto &bulletTC = bullet.GetComponent<TransformComponent>();
        auto &tc = GetComponent<TransformComponent>();

        bulletTC.Translation.x = tc.Translation.x + 0.7f;
        bulletTC.Translation.y = tc.Translation.y - 0.05f;

        bullet.AddComponent<Health>(1);

        _IsAttacking = true;
    }

    void Player::Charge() {
        EXODIA_INFO("Attack charged for '{0}' seconds", _AttackTimer);

        Scene *scene = HandleEntity.GetScene();

        if (!scene)
            return;
        GameObject bullet = scene->LoadPrefabs(
            (Project::GetActiveAssetDirectory() / "Prefabs/Bullets/SuperBullet.prefab").string(), true);

        bullet.GetComponent<TagComponent>().Tag = "BP";
        auto &bulletID = bullet.GetComponent<IDComponent>();

        bullet.AddComponent<ParentComponent>().Parent = GetComponent<IDComponent>().ID;
        GetComponent<ChildrenComponent>().Children.push_back(bulletID.ID);

        auto &bulletTC = bullet.GetComponent<TransformComponent>();
        auto &tc = GetComponent<TransformComponent>();

        bulletTC.Translation.x = tc.Translation.x + 1.0f;
        bulletTC.Translation.y = tc.Translation.y;

        auto &health = bullet.AddComponent<Health>();
        health.CurrentHealth = std::ceil(_AttackTimer);

        _AttackTimer = 0.0f;
        _IsCharging = false;
    }

    ///////////////////////
    // Getters & Setters //
    ///////////////////////

    PlayerState Player::GetState() const { return _State; }

    void Player::SetState(PlayerState state) {
        _PreviousState = _State;
        _State = state;
    }
}; // namespace RType