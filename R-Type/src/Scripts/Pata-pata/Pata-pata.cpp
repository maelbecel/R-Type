/*
** EPITECH PROJECT, 2023
** $
** File description:
** Pata-pata
*/

#include "Pata-pata.hpp"
#include "Event/TakeDamage.hpp"

using namespace Exodia;

namespace RType {

    void PataPata::CreateAnimations() {
        AnimationComponent anim;
        AnimationComponent death;

        std::vector<Ref<SubTexture2D>> framesIdle;
        std::vector<Ref<SubTexture2D>> framesDeath;

        for (int i = 0; i < 8; i++)
            framesIdle.push_back(SubTexture2D::CreateFromCoords(PATAPATA, {i, 0.0f}, {33.3125f, 36.0f}, {1.0f, 1.0f}));
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

    void PataPata::OnCreate() {
        HandleEntity.AddComponent<Health>(1);
        HandleEntity.AddComponent<Clock>();
        HandleEntity.AddComponent<BoxCollider2DComponent>();

        RigidBody2DComponent &rb = HandleEntity.AddComponent<RigidBody2DComponent>();

        rb.Type = RigidBody2DComponent::BodyType::Dynamic;
        rb.Mass = 0.0f;
        rb.GravityScale = 0.0f;
        rb.Velocity.x = 0.0f;

        CreateAnimations();

        TransformComponent &tc = GetComponent<TransformComponent>();

        tc.Translation.x = 7.0f;
        // tc.Translation.y = (float)(std::rand() % 10 - 5);
        tc.Translation.y = 0.0f;
    }

    void PataPata::UpdateAnimations() {
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

    void PataPata::OnUpdate(Timestep ts) {
        IsDead();
        UpdateAnimations();
        SinusoidalMovement(ts);
        Shoot();
    }

    void PataPata::OnCollisionEnter(Entity *entity) {
        ComponentHandle<TagComponent> tag = entity->GetComponent<TagComponent>();
        Health &health = GetComponent<Health>();

        if (!tag) {
            EXODIA_WARN("PataPata: has no tag component found");

            return;
        }
        std::string entityTag = tag.Get().Tag;

        if (entityTag.rfind("Bullet", 0) == 0) {
            EXODIA_INFO("Bullet {0} hit", entityTag);

            HandleEntity.GetScene()->GetWorldPtr()->Emit<Events::TakeDamage>({HandleEntity.GetEntity(), 1});
        }
    }

    void PataPata::Shoot() {
        TransformComponent &tc = GetComponent<TransformComponent>();

        if (_State == State::DEAD)
            return;
        if (_AttackTimer > _AttackCooldown) {
            Scene *scene = HandleEntity.GetScene();

            if (!scene)
                return;
            GameObject bullet = scene->CreateNewEntity("BE" + std::to_string(scene->GetWorldPtr()->GetCount()));

            if (!bullet.GetEntity())
                return;

            ScriptComponent &script = bullet.AddComponent<ScriptComponent>();

            script.Bind("BulletEnnemy");

            ParentComponent &parent = bullet.AddComponent<ParentComponent>();
            IDComponent &ID = GetComponent<IDComponent>();

            parent.Parent = ID.ID;
            _AttackTimer = 0.0f;
        }
    }

    void PataPata::SinusoidalMovement(Timestep ts) {
        RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();
        Clock &clock = GetComponent<Clock>();

        _AttackTimer += ts.GetSeconds();

        // Parameters of the sinusoidal movement
        double amplitude = 5.0f; // Amplitude of the sinusoidal movement
        double frequency = 1.0f; // Frequency of the sinusoidal movement
        float &mytime = clock.ElapsedTime;

        if (_State == State::ALIVE) {
            mytime += ts.GetSeconds();

            body.Velocity.y = (float)(amplitude * sin(frequency * mytime * PI));
        }
    }

    void PataPata::IsDead() {
        Health &health = GetComponent<Health>();
        RigidBody2DComponent &body = GetComponent<RigidBody2DComponent>();

        if (_State == State::ALIVE && health.CurrentHealth <= 0) {
            _State = State::DEAD;
            body.Velocity = {0.0f, 0.0f};
        }
    }
}; // namespace RType
