/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DefaultPlayer
*/

#include "DefaultLayer.hpp"
#include "Script/Player/Player.hpp"
#include "Script/Pata-pata.hpp"
#include "Script/Star.hpp"
#include "Script/ExampleScript.hpp"
#include "Script/Button.hpp"
#include "Script/Camera.hpp"
#include "ComponentExample.hpp"
#include "AnimationSystem.hpp"


namespace Exodia {

    // -- Layer ----------------------------------------------------------------

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    DefaultLayer::DefaultLayer() : Layer("DefaultLayer"), _CameraController(1600.0f / 900.0f) {};

    /////////////
    // Methods //
    /////////////


    void DefaultLayer::RegisterComponent(std::string name, std::function<IComponentContainer *(Buffer)> factory) {
        _ComponentFactory.emplace(name, factory);
    }

    void DefaultLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        // Register components
        RegisterComponent("IDComponent", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<IDComponent>(); });
        RegisterComponent("TransformComponent", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<TransformComponent>(); });
        RegisterComponent("SpriteRendererComponent", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<SpriteRendererComponent>(); });
        RegisterComponent("BoxCollider2DComponent", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<BoxCollider2DComponent>(); });
        RegisterComponent("CircleRendererComponent", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<CircleRendererComponent>(); });
        RegisterComponent("RigidBody2DComponent", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<RigidBody2DComponent>(); });
        RegisterComponent("ScriptComponent", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<ScriptComponent>(); });
        RegisterComponent("Health", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<Health>(); });
        RegisterComponent("Animation", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<Animation>(); });
        RegisterComponent("Clock", [](UNUSED Buffer data) -> IComponentContainer * { return new ComponentContainer<Clock>(); });


        // Create world
        _currentScene = MENU;
        _World[GAME] = CreateRef<Scene>();
        _World[MENU] = CreateRef<Scene>();
        _World[GAME]->OnViewportResize(1600, 900);
        _World[MENU]->OnViewportResize(1600, 900);

        _World[GAME]->RegisterSystem(new AnimationSystem());
        _World[GAME]->RegisterSystem(new ScriptSystem());
        _World[GAME]->RegisterSystem(new MovingSystem(1.5f));

        _World[MENU]->RegisterSystem(new AnimationSystem());
        _World[MENU]->RegisterSystem(new ScriptSystem());
        _World[MENU]->RegisterSystem(new MovingSystem(1.5f));


        // camera->AddComponent<ScriptComponent>().Get().Bind<CameraScript>();

        Entity *cameraEntity = _World[GAME]->CreateEntity("Camera");
        auto &camera = cameraEntity->AddComponent<CameraComponent>().Get();
        cameraEntity->GetComponent<TransformComponent>().Get().Translation = { 0.0f, 0.0f, 15.0f };
        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(1600, 900);

        auto body_camera = cameraEntity->AddComponent<RigidBody2DComponent>();
        body_camera.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_camera.Get().Mass = 0.0f;
        body_camera.Get().GravityScale = 0.0f;
        body_camera.Get().Velocity = glm::vec2{ 1.5f, 0.0f };



        CollisionSystem *collisionSystem = new CollisionSystem();
        _World[GAME]->RegisterSystem(collisionSystem);
        _World[GAME]->Subscribe<Events::OnCollisionEntered>(collisionSystem);

        // Create player
        CreatePlayer();

        // Create pata-pata
        Entity *patata = _World[GAME]->CreateEntity("Pata-pata");

        auto sprite = patata->AddComponent<SpriteRendererComponent>();
        patata->AddComponent<Health>(1);
        patata->AddComponent<ScriptComponent>().Get().Bind<PataPata>();
        patata->AddComponent<Animation>(1.0f, 8.0f, 0.1f);
        patata->AddComponent<Clock>();
        patata->AddComponent<BoxCollider2DComponent>();

        auto body_patata = patata->AddComponent<RigidBody2DComponent>();

        body_patata.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_patata.Get().Mass = 0.0f;
        body_patata.Get().GravityScale = 0.0f;
        body_patata.Get().Velocity.x = -2.0f;
        // Set entity sprite
        Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Pata-Pata.png");
        sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 0.0f }, { 33.3125f, 36.0f }, { 1.0f, 1.0f });


        // Create background
        Entity *background = _World[GAME]->CreateEntity("Background");

        background->AddComponent<IDComponent>();
        background->AddComponent<CircleRendererComponent>(glm::vec4{ 0.0f, 0.0f, 0.005f, 1.0f });
        background->GetComponent<TransformComponent>().Get().Scale.y = 100.0f;
        background->GetComponent<TransformComponent>().Get().Scale.x = 100.0f;
        background->GetComponent<TransformComponent>().Get().Translation.z = -0.5f;

        auto body_bg = background->AddComponent<RigidBody2DComponent>();
        body_bg.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_bg.Get().Mass = 0.0f;
        body_bg.Get().GravityScale = 0.0f;
        body_bg.Get().Velocity = glm::vec2{ 1.5f, 0.0f };


        Entity *button = _World[MENU]->CreateEntity("Button");

        button->AddComponent<IDComponent>();
        button->AddComponent<CircleRendererComponent>(glm::vec4{ 0.8f, 0.0f, 0.005f, 1.0f });
        button->AddComponent<ScriptComponent>().Get().Bind<ButtonScript>();
        button->GetComponent<TransformComponent>().Get().Scale.y = 4.0f;
        button->GetComponent<TransformComponent>().Get().Scale.x = 4.0f;
        button->GetComponent<TransformComponent>().Get().Translation.z = -0.5f;

        auto buttonBody = button->AddComponent<RigidBody2DComponent>();
        buttonBody.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        buttonBody.Get().Mass = 0.0f;
        buttonBody.Get().GravityScale = 0.0f;
        buttonBody.Get().Velocity = glm::vec2{ 0.0f, 0.0f };

        Entity *cameraMenu = _World[MENU]->CreateEntity("Camera");
        auto &camera_ = cameraMenu->AddComponent<CameraComponent>().Get();
        cameraMenu->GetComponent<TransformComponent>().Get().Translation = { 0.0f, 0.0f, 15.0f };
        camera_.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera_.Camera.SetViewportSize(1600, 900);
        cameraMenu->AddComponent<RigidBody2DComponent>().Get().Type = RigidBody2DComponent::BodyType::Static;

        // Create stars
		for(int i = 0; i < 60; i++) {
            Entity *star = _World[GAME]->CreateEntity("Star" + std::to_string(i));

            star->AddComponent<ScriptComponent>().Get().Bind<Star>();
            star->GetComponent<TransformComponent>().Get().Scale.y = 0.1f;
            star->GetComponent<TransformComponent>().Get().Scale.x = 0.1f;
            star->AddComponent<Clock>();
			star->AddComponent<CircleRendererComponent>(glm::vec4{ 0.9f, 0.9f, 0.9f + static_cast<float>(random() % 100) / 10000.0f, 0.9f });

            auto body = star->AddComponent<RigidBody2DComponent>();

            body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
            body.Get().Mass = 0.0f;
            body.Get().GravityScale = 0.0f;
            body.Get().Velocity.x = (random() % 10 + 1) * -1;
        }


        // Create camera
        _CameraController.SetZoomLevel(5.0f);
        _World[_currentScene]->OnRuntimeStart();
    }

    void DefaultLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void DefaultLayer::OnUpdate(Timestep ts)
    {
        // Update
        _CameraController.OnUpdate(ts);


        // Renderer Prep
        RenderCommand::SetClearColor({ 1.0f, 1.0f, 1.0f, 1 });
        RenderCommand::Clear();

        if (_currentScene == GAME) {
            auto pata = _World[GAME]->GetEntityByName("Pata-pata");
            if (pata == nullptr) {
                Entity *patata = _World[GAME]->CreateEntity("Pata-pata");

                auto sprite = patata->AddComponent<SpriteRendererComponent>();
                patata->AddComponent<Health>(1);
                patata->AddComponent<ScriptComponent>().Get().Bind<PataPata>();
                patata->AddComponent<Animation>(1.0f, 8.0f, 0.075f);
                patata->AddComponent<Clock>();
                patata->AddComponent<BoxCollider2DComponent>();

                auto body_patata = patata->AddComponent<RigidBody2DComponent>();

                body_patata.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
                body_patata.Get().Mass = 0.0f;
                body_patata.Get().GravityScale = 0.0f;
                body_patata.Get().Velocity.x = -2.0f;
                // Set entity sprite
                Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Pata-Pata.png");
                sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 0.0f, 0.0f }, { 33.3125f, 36.0f }, { 1.0f, 1.0f });

            }
        }
        _World[_currentScene]->OnUpdateRuntime(ts);
    }

    void DefaultLayer::OnEvent(Event &event)
    {
        _CameraController.OnEvent(event);
    }

    // ------------------------------------------------------------------

    void DefaultLayer::CreatePlayer()
    {
        Entity *entity = _World[GAME]->CreateEntity("Player");

        entity->AddComponent<Health>(1);
        entity->AddComponent<ScriptComponent>().Get().Bind<Player>();
        entity->AddComponent<Animation>(1.0f, 2.0f, 0.1f);
        entity->GetComponent<TransformComponent>().Get().Scale.y = 0.5f;
        entity->AddComponent<BoxCollider2DComponent>();
        auto sprite = entity->AddComponent<SpriteRendererComponent>();

        // Set entity sprite
        Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Player.png");
        sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture, { 2.0f, 4.0f }, { 33.2f, 17.2f }, { 1.0f, 1.0f });

        // Set entity rigidbody
        auto body = entity->AddComponent<RigidBody2DComponent>();

        body.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body.Get().Mass = 0.0f;
        body.Get().GravityScale = 0.0f;
        body.Get().Velocity = glm::vec2{ 0.0f, 0.0f };
    }
};
