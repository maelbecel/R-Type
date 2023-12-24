/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DefaultLayer.hpp"
#include "Script/Player.hpp"

namespace Exodia {

    // -- Layer ----------------------------------------------------------------

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    DefaultLayer::DefaultLayer() : Layer("DefaultLayer"), _CameraController(1280.0f / 720.0f){};

    /////////////
    // Methods //
    /////////////

    void DefaultLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        _World = World::CreateWorld();

        Entity *entity = _World->CreateEntity("Player");

        entity->AddComponent<SpriteRendererComponent>(glm::vec4{0.8f, 0.2f, 0.3f, 1.0f});
        entity->AddComponent<ScriptComponent>().Get().Bind<Player>();
        entity->AddComponent<BoxCollider2DComponent>();
        entity->GetComponent<TransformComponent>().Get().Translation = glm::vec3{0.0f, 5.0f, 0.0f};

        auto body = entity->AddComponent<RigidBody2DComponent>();

        body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body.Get().Mass = 1.0f;
        body.Get().GravityScale = 1.0f;
        body.Get().Velocity = glm::vec2{1.0f, 0.0f};

        Entity *Obstacle = _World->CreateEntity("Obstacle");

        Obstacle->AddComponent<SpriteRendererComponent>(glm::vec4{0.2f, 0.8f, 0.3f, 1.0f});
        Obstacle->AddComponent<BoxCollider2DComponent>();
        Obstacle->AddComponent<RigidBody2DComponent>().Get().Type = RigidBody2DComponent::BodyType::Static;
        auto &transform = Obstacle->GetComponent<TransformComponent>().Get();

        transform.Translation = glm::vec3{2.0f, -2.0f, 0.0f};
        transform.Scale = glm::vec3{15.0f, 2.0f, 1.0f};

        CollisionSystem *collisionSystem = new CollisionSystem();

        _World->RegisterSystem(new ScriptSystem());
        _World->RegisterSystem(new GravitySystem(1.5f));
        _World->RegisterSystem(new MovingSystem(1.5f));
        _World->RegisterSystem(collisionSystem);

        _World->Subscribe<Events::OnCollisionEntered>(collisionSystem);

        _CameraController.SetZoomLevel(5.0f);
    }

    void DefaultLayer::OnDetach() {
        EXODIA_PROFILE_FUNCTION();

        _World->DestroyWorld();
    }

    void DefaultLayer::OnUpdate(Exodia::Timestep ts) {
        // Update
        _CameraController.OnUpdate(ts);

        _World->Update(ts);

        // Renderer Prep
        Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Exodia::RenderCommand::Clear();

        Renderer2D::BeginScene(_CameraController.GetCamera());

        _World->ForEach<SpriteRendererComponent>([&](Entity *entity, ComponentHandle<SpriteRendererComponent> sprite) {
            auto transform = entity->GetComponent<TransformComponent>();
            auto id = entity->GetComponent<IDComponent>();

            if (transform && id) {
                Renderer2D::DrawSprite(transform.Get().GetTransform(), // Transform
                                       sprite.Get(),                   // SpriteRendererComponent
                                       (int)id.Get().ID                // Entity ID
                );
            }
        });

        Renderer2D::EndScene();
    }

    void DefaultLayer::OnEvent(Event &event) { _CameraController.OnEvent(event); }
}; // namespace Exodia
