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

        HandleEntity->AddComponent<Health>(1);
        HandleEntity->AddComponent<Clock>();
        HandleEntity->AddComponent<BoxCollider2DComponent>();

        ComponentHandle<RigidBody2DComponent> body = HandleEntity->AddComponent<RigidBody2DComponent>();

        if (!body)
            return;

        RigidBody2DComponent &rb = body.Get();
        rb.Type = RigidBody2DComponent::BodyType::Dynamic;
        rb.Mass = 0.0f;
        rb.GravityScale = 0.0f;
        rb.Velocity.x = 0.0f;

        CreateAnimations();
        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();

        if (!transform)
            return;

        TransformComponent &tc = transform.Get();

        tc.Translation.x = 7.0f;
        // tc.Translation.y = (float)(std::rand() % 10 - 5);
        tc.Translation.y = 0.0f;

        EXODIA_INFO("PataPata created at pos {0}, {1}", tc.Translation.x, tc.Translation.y);
    }

    void PataPata::UpdateAnimations() {
        ComponentHandle<SpriteRendererComponent> sprite = GetComponent<SpriteRendererComponent>();
        ComponentHandle<AnimationComponent> anim = GetComponent<AnimationComponent>();

        if (!sprite)
            sprite = HandleEntity->AddComponent<SpriteRendererComponent>();

        if (!anim) {
            _Animations[0].IsPlaying = true;

            anim = HandleEntity->AddComponent<AnimationComponent>(_Animations[0]);

            sprite.Get().Texture = anim.Get().Frames[0];
        } else {
            SpriteRendererComponent &sr = sprite.Get();
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
                    World *world = HandleEntity->GetWorld();
                    if (!world)
                        return;
                    world->DestroyEntity(HandleEntity);
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
        ComponentHandle<Health> health = GetComponent<Health>();

        if (!tag || !health) {
            EXODIA_WARN("PataPata: No tag or health component found");
            return;
        }

        std::string entityTag = tag.Get().Tag;

        if (entityTag.rfind("Bullet", 0) == 0) {
            EXODIA_INFO("Bullet {0} hit", entityTag);

            HandleEntity->GetWorld()->Emit<Events::TakeDamage>({HandleEntity, 1});
            // health.Get().CurrentHealth -= 1;
        }
    }

    void PataPata::Shoot() {
        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();

        if (_State == State::DEAD)
            return;
        if (!transform)
            return;

        TransformComponent tc = transform.Get();

        if (_AttackTimer > _AttackCooldown) {
            World *world = HandleEntity->GetWorld();
            if (!world)
                return;

            Entity *bullet = world->CreateNewEntity("BE" + std::to_string(world->GetCount()));
            if (!bullet)
                return;

            ComponentHandle<ScriptComponent> script = bullet->AddComponent<ScriptComponent>();
            if (!script)
                return;
            script.Get().Bind("BulletEnnemy");

            ComponentHandle<ParentComponent> parent = bullet->AddComponent<ParentComponent>();
            ComponentHandle<IDComponent> ID = HandleEntity->GetComponent<IDComponent>();
            if (!parent || !ID)
                return;
            parent.Get().Parent = ID.Get().ID;
            _AttackTimer = 0.0f;
        }
    }

    void PataPata::SinusoidalMovement(Timestep ts) {
        ComponentHandle<RigidBody2DComponent> body = GetComponent<RigidBody2DComponent>();
        ComponentHandle<Clock> clock = GetComponent<Clock>();

        _AttackTimer += ts.GetSeconds();

        if (!clock || !body)
            return;

        // Parameters of the sinusoidal movement
        double amplitude = 5.0f; // Amplitude of the sinusoidal movement
        double frequency = 1.0f; // Frequency of the sinusoidal movement
        float &mytime = clock.Get().ElapsedTime;

        if (_State == State::ALIVE) {
            mytime += ts.GetSeconds();
            body.Get().Velocity.y = (float)(amplitude * sin(frequency * mytime * PI));
        }
    }

    void PataPata::IsDead() {
        ComponentHandle<Health> health = GetComponent<Health>();
        ComponentHandle<RigidBody2DComponent> body = GetComponent<RigidBody2DComponent>();

        if (!health || !body) {
            EXODIA_WARN("PataPata has no health or body");
            return;
        }

        if (_State == State::ALIVE && health.Get().CurrentHealth <= 0) {
            _State = State::DEAD;
            body.Get().Velocity = {0.0f, 0.0f};
        }
    }

} // namespace RType