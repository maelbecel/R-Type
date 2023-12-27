/*
** EPITECH PROJECT, 2023
** $
** File description:
** Pata-pata
*/

#include "Pata-pata.hpp"

using namespace Exodia;

namespace RType {

    void PataPata::OnCreate() {

        HandleEntity->AddComponent<Health>(1);
        HandleEntity->AddComponent<Animation>(1.0f, 8.0f, 0.1f);
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

        // Set entity sprite
        // auto sprite = HandleEntity->AddComponent<SpriteRendererComponent>(glm::vec4{0.8f, 0.2f, 0.3f, 1.0f});
        // sprite.Get().Texture =
        //     SubTexture2D::CreateFromCoords(90123456789012678, {0.0f, 0.0f}, {33.3125f, 36.0f}, {1.0f, 1.0f});
        HandleEntity->AddComponent<CircleRendererComponent>(glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f});

        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();

        if (!transform)
            return;

        TransformComponent &tc = transform.Get();

        tc.Translation.x = 7.0f;
        tc.Translation.y = (float)(std::rand() % 10 - 5);

        // Set variables
        _State = State::ALIVE;
        EXODIA_INFO("PataPata created at pos {0}, {1}", tc.Translation.x,
                    tc.Translation.y);
    }

    void PataPata::OnUpdate(Timestep ts) {
        ComponentHandle<TransformComponent> transform = GetComponent<TransformComponent>();

        if (!transform)
            return;

        IsDead();
        SinusoidalMovement(ts);
        Shoot(transform);
    }

    void PataPata::OnCollisionEnter(Entity *entity) {
        std::string entityTag = entity->GetComponent<TagComponent>().Get().Tag;

        if (!entityTag.empty())
            return;

        if (entityTag.rfind("Bullet", 0) == 0) {
            EXODIA_INFO("Bullet {0} hit", entity->GetComponent<TagComponent>().Get().Tag);
            GetComponent<Health>().Get().CurrentHealth -= 1;
        }
    }

    void PataPata::Shoot(ComponentHandle<TransformComponent> transform) {
        if (_State == State::DEAD)
            return;
        if (!transform)
            return;

        TransformComponent tc = transform.Get();

        if (_AttackTimer > 1.0f) {
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
        ComponentHandle<Clock> time = GetComponent<Clock>();

        _AttackTimer += ts.GetSeconds();

        if (!time || !body)
            return;

        // Parameters of the sinusoidal movement
        double amplitude = 5.0f; // Amplitude of the sinusoidal movement
        double frequency = 1.0f; // Frequency of the sinusoidal movement
        float &mytime = time.Get().ElapsedTime;

        if (_State == State::ALIVE) {
            mytime += ts.GetSeconds();
            body.Get().Velocity.y = (float)(amplitude * sin(frequency * mytime * PI));
        }
    }

    void PataPata::IsDead() {
        ComponentHandle<Animation> animation = GetComponent<Animation>();
        ComponentHandle<Health> health = GetComponent<Health>();
        ComponentHandle<RigidBody2DComponent> body = GetComponent<RigidBody2DComponent>();

        if (!animation || !health || !body)
            return;

        Animation &ac = animation.Get();

        if (_State == State::ALIVE && health.Get().CurrentHealth <= 0) {
            ac.CurrentFrame = 0;
            ac.MaxFrame = 7;
            ac.FrameTime = 0.095f;

            // Set entity sprite to explosion
            // auto sprite = GetComponent<SpriteRendererComponent>();
            // if (!sprite)
            //     return;
            // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Simple_Explosion.png");
            // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 0.0f, 0.0f }, { 32.0f, 34.0f
            // }, { 1.0f, 1.0f });
            _State = State::DEAD;
            body.Get().Velocity = { 0.0f, 0.0f };
        }

        if (_State == State::DEAD && ac.CurrentFrame == ac.MaxFrame - 1) {
            HandleEntity->GetWorld()->DestroyEntity(HandleEntity);
        }
    }

} // namespace Exodia