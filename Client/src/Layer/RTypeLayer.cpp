/*
** EPITECH PROJECT, 2023
** ExodiaGameEngine
** File description:
** ExodiaEngine
*/

#include "RTypeLayer.hpp"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Exodia {

    //////////////////////////////
    // Constructor & Destructor //
    //////////////////////////////

    RTypeLayer::RTypeLayer() : Layer("R-Type"), network(_worldNetwork, ioContextManager, 8083), _CameraController(1600.0f / 900.0f)
    {

    };

    /////////////
    // Methods //
    /////////////

    void RTypeLayer::RegisterComponent(std::string name, std::function<IComponentContainer *(Buffer)> factory) {
        _ComponentFactory.emplace(name, factory);
    }

    void RTypeLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        // Register components
        RegisterComponent("IDComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<IDComponent>(); });
        RegisterComponent("TransformComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<TransformComponent>(); });
        RegisterComponent("SpriteRendererComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<SpriteRendererComponent>(); });
        RegisterComponent("BoxCollider2DComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<BoxCollider2DComponent>(); });
        RegisterComponent("CircleRendererComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<CircleRendererComponent>(); });
        RegisterComponent("RigidBody2DComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<RigidBody2DComponent>(); });
        RegisterComponent("ScriptComponent", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<ScriptComponent>(); });
        RegisterComponent("Health", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<Health>(); });
        RegisterComponent("Animation", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<Animation>(); });
        RegisterComponent("Clock", [](UNUSED(Buffer data)) -> IComponentContainer * { return new ComponentContainer<Clock>(); });

        // if (commandLine.Count > 1) {
        //     Application::Get().Close();
        //     return;
        // }

        FramebufferSpecification fbSpec;

        fbSpec.Width  = Application::Get().GetWindow().GetWidth();
        fbSpec.Height = Application::Get().GetWindow().GetHeight();
        fbSpec.Attachments = {
            FramebufferTextureFormat::RGBA8,
            FramebufferTextureFormat::RED_INTEGER,
            FramebufferTextureFormat::Depth
        };

        _Framebuffer = Framebuffer::Create(fbSpec);

        // Server main
        //Exodia::Network::IOContextManager ioContextManager;

        // Define a local endpoint to listen on
        // asio::ip::udp::endpoint localEndpoint(asio::ip::address::from_string("127.0.0.1"), 8082);
        network.Loop();
        network.SendAskConnect("0.0.0.0", 8082);

        // Create world
        _currentScene = GAME;
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

        CollisionSystem *collisionSystem = new CollisionSystem();
        _World[GAME]->RegisterSystem(collisionSystem);
        _World[GAME]->Subscribe<Events::OnCollisionEntered>(collisionSystem);

        // Create the camera entity
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

        // Create the entities
        CreatePlayer(_World, 0);

        // Create pata-pata
        CreatePataPata(_World);

        // Create background
        CreateBackground(_World);

        Entity *cameraMenu = _World[MENU]->CreateEntity("Camera");
        auto &camera_ = cameraMenu->AddComponent<CameraComponent>().Get();
        cameraMenu->GetComponent<TransformComponent>().Get().Translation = { 0.0f, 0.0f, 15.0f };
        camera_.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera_.Camera.SetViewportSize(1600, 900);
        cameraMenu->AddComponent<RigidBody2DComponent>().Get().Type = RigidBody2DComponent::BodyType::Static;

        // Create stars
        CreateStars(_World);

        // Create the camera
        _CameraController.SetZoomLevel(5.0f);
        _World[_currentScene]->OnRuntimeStart();
    }

    void RTypeLayer::OnDetach()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void RTypeLayer::OnUpdate(Exodia::Timestep ts)
    {
        EXODIA_PROFILE_FUNCTION();

        // Renderer Prep
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Exodia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Exodia::RenderCommand::Clear();
        }

        // Update
        _CameraController.OnUpdate(ts);

        if (_currentScene == GAME) {
            auto pata = _World[GAME]->GetEntityByName("Pata-pata");
            if (pata == nullptr) {
                Entity *patata = _World[GAME]->CreateEntity("Pata-pata");

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
                // auto sprite = patata->AddComponent<SpriteRendererComponent>();
                // Ref<Texture2D> texture = TextureImporter::LoadTexture2D("Assets/Textures/Pata-Pata.png");
                // sprite.Get().Texture = SubTexture2D::CreateFromCoords(texture->Handle, { 0.0f, 0.0f }, { 33.3125f, 36.0f }, { 1.0f, 1.0f });

            }
        }
        // Update the world
        _World[_currentScene]->OnUpdateRuntime(ts);
    }

    void RTypeLayer::OnImGUIRender()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void RTypeLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyReleasedEvent));

    }

    bool RTypeLayer::OnKeyPressedEvent(KeyPressedEvent &event) {

        int key = event.GetKeyCode();

        EXODIA_INFO("pressed {0}", key);
        _World[_currentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](Entity *entity, auto script, auto tag) {
            (void)entity;

            if (tag.Get().Tag.rfind("Player", 0) != std::string::npos && script.Get().Instance != nullptr) {
                script.Get().Instance->OnKeyPressed(key);
                network.SendEvent(key);
            }
        });
        return true;

    };

    bool RTypeLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {

        int key = event.GetKeyCode();

        EXODIA_INFO("released {0}", key);

        _World[_currentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](Entity *entity, auto script, auto tag) {
            (void)entity;

            if (tag.Get().Tag.rfind("Player", 0) != std::string::npos && script.Get().Instance != nullptr) {
                script.Get().Instance->OnKeyReleased(key);
            }
        });
        return false;
    };
};
