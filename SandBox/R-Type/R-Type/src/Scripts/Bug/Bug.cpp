/*
** EPITECH PROJECT, 2023
** $
** File description:
** Bug
*/

#include "Bug.hpp"
#include "Event/TakeDamage.hpp"

using namespace Exodia;

namespace RType {

    void Bug::CreateAnimations() {
        AnimationComponent anim;
        AnimationComponent death;

        std::vector<Ref<SubTexture2D>> framesIdle;
        std::vector<Ref<SubTexture2D>> framesDeath;

        for (int i = 6; i < 8; i++)
            framesIdle.push_back(SubTexture2D::CreateFromCoords(BUG, {i, 1.0f}, {33.25f, 34.0}, {1.0f, 1.0f}));
        for (int i = 0; i < 3; i++)
            framesIdle.push_back(SubTexture2D::CreateFromCoords(BUG, {i, 0.0f}, {33.25f, 34.0}, {1.0f, 1.0f}));
        for (int i = 0; i < 6; i++)
            framesDeath.push_back(SubTexture2D::CreateFromCoords(DEATH, {i, 0.0f}, {32.0f, 34.0f}, {1.0f, 1.0f}));

        anim.Frames = framesIdle;
        anim.IsPlaying = false;
        anim.Repeat = true;
        anim.FrameRate = TimeBetweenAnimations;

        death.Frames = framesDeath;
        death.IsPlaying = false;
        death.Repeat = false;
        death.FrameRate = TimeBetweenAnimations;

        _Animations.push_back(anim);
        _Animations.push_back(death);
    }

    void Bug::OnCreate() {
        HandleEntity.AddComponent<Health>(1);
        HandleEntity.AddComponent<Clock>();
        HandleEntity.AddComponent<BoxCollider2DComponent>();

        RigidBody2DComponent &rb = HandleEntity.AddComponent<RigidBody2DComponent>();

        rb.Type = RigidBody2DComponent::BodyType::Dynamic;
        rb.Mass = 0.0f;
        rb.GravityScale = 0.0f;
        rb.Velocity.x = -0.0f;

        CreateAnimations();

        TransformComponent &tc = GetComponent<TransformComponent>();

        tc.Translation.x = 7.0f;
        tc.Translation.y = -1.5f;

        EXODIA_INFO("Bug created at pos {0}, {1}", tc.Translation.x, tc.Translation.y);
    }

    void Bug::UpdateAnimations() {
        SpriteRendererComponent &sr = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = HandleEntity.GetEntity()->GetComponent<AnimationComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;

            anim = HandleEntity.GetEntity()->AddComponent<AnimationComponent>(_Animations[0]);

            sr.Texture = anim.Get().Frames[0];
        } else {
            AnimationComponent &ac = anim.Get();

            if (_State == State::ALIVE && _PreviousState != State::ALIVE) {
                _Animations[0].IsPlaying = true;
                _Animations[1].IsPlaying = false;
                _PreviousState = State::ALIVE;

                ac = _Animations[0];
                sr.Texture = ac.Frames[0];
            } else if (_State == State::DEAD && _PreviousState != State::DEAD) {
                _Animations[0].IsPlaying = false;
                _Animations[1].IsPlaying = true;
                _PreviousState = State::DEAD;

                ac = _Animations[1];
                sr.Texture = ac.Frames[0];
            } else if (_State == State::DEAD && _PreviousState == State::DEAD) {
                if (ac.CurrentFrameIndex == ac.Frames.size() - 1) {
                    Scene *scene = HandleEntity.GetScene();

                    if (!scene)
                        return;
                    scene->DestroyEntity(HandleEntity);
                }
            }
        }
    }

    void Bug::OnUpdate(Timestep ts) {
        IsDead();
        UpdateAnimations();
        SinusoidalMovement(ts);
        Shoot();
    }

    void Bug::SinusoidalMovement(Timestep ts) {
        RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();
        Clock &clock = GetComponent<Clock>();

        _AttackTimer += ts.GetSeconds();

        // Parameters of the sinusoidal movement
        double amplitude = 1.0f; // Amplitude of the sinusoidal movement
        double frequency = 1.0f; // Frequency of the sinusoidal movement

        if (_State == State::ALIVE) {
            clock.ElapsedTime += ts.GetSeconds();

            body.Velocity.y = (float)(amplitude * sin(frequency * clock.ElapsedTime * RType::PI));
        }
    }

    void Bug::Shoot() {
        if (_State == State::DEAD)
            return;
        if (_AttackTimer > _AttackCooldown) {
            Scene *scene = HandleEntity.GetScene();

            if (!scene)
                return;
            GameObject bullet = scene->LoadPrefabs(
                (Project::GetActiveAssetDirectory() / "Prefabs/Bullets/BulletEnemy.prefab").string(), true);

            bullet.GetComponent<TagComponent>().Tag = "BE";
            auto &bulletID = bullet.GetComponent<IDComponent>();

            bulletID.ID = UUID();

            bullet.AddComponent<ParentComponent>().Parent = GetComponent<IDComponent>().ID;
            GetComponent<ChildrenComponent>().Children.push_back(bulletID.ID);

            auto &bulletTC = bullet.GetComponent<TransformComponent>();
            auto &tc = GetComponent<TransformComponent>();

            bulletTC.Translation.x = tc.Translation.x;
            bulletTC.Translation.y = tc.Translation.y;

            _AttackTimer = 0.0f;
        }
    }

    void Bug::IsDead() {
        Health &health = GetComponent<Health>();
        RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();

        if (_State == State::ALIVE && health.CurrentHealth <= 0) {
            _State = State::DEAD;
            body.Velocity = {0.0f, 0.0f};
        }
    }

} // namespace RType