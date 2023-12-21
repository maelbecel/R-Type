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
        Exodia::Network::IOContextManager ioContextManager;

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
        CreatePlayer(_World);


        // Create pata-pata
        CreatePataPata(_World);

        // Create background
        CreateBackground(_World);

        // Entity *button = _World[MENU]->CreateEntity("Button");

        // button->AddComponent<IDComponent>();
        // button->AddComponent<CircleRendererComponent>(glm::vec4{ 0.8f, 0.0f, 0.005f, 1.0f });
        // button->AddComponent<ScriptComponent>().Get().Bind<ButtonScript>();
        // button->GetComponent<TransformComponent>().Get().Scale.y = 4.0f;
        // button->GetComponent<TransformComponent>().Get().Scale.x = 4.0f;
        // button->GetComponent<TransformComponent>().Get().Translation.z = -0.5f;

        // auto buttonBody = button->AddComponent<RigidBody2DComponent>();
        // buttonBody.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        // buttonBody.Get().Mass = 0.0f;
        // buttonBody.Get().GravityScale = 0.0f;
        // buttonBody.Get().Velocity = glm::vec2{ 0.0f, 0.0f };

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

        // Update
        _CameraController.OnUpdate(ts);

        // Update the world
        _World[_currentScene]->OnUpdateRuntime(ts);

        // // Renderer Draw
        // {
        //     EXODIA_PROFILE_SCOPE("Renderer Draw");
        //     Exodia::Renderer2D::BeginScene(_CameraController.GetCamera());

        //     _World->ForEach<CircleRendererComponent>([&](Entity *entity, ComponentHandle<CircleRendererComponent> circle) {
        //         auto transform = entity->GetComponent<TransformComponent>();
        //         auto id = entity->GetComponent<IDComponent>();

        //         if (transform && id) {
        //             Renderer2D::DrawCircle(
        //                 transform.Get().GetTransform(), // Transform
        //                 circle.Get().Color, // CircleRendererComponent
        //                 circle.Get().Thickness, // CircleRendererComponent
        //                 circle.Get().Fade, // CircleRendererComponent
        //                 (int)id.Get().ID                // Entity ID
        //             );
        //         }
        //     });

        //     _World->ForEach<SpriteRendererComponent>([&](Entity *entity, ComponentHandle<SpriteRendererComponent> sprite) {
        //         auto transform = entity->GetComponent<TransformComponent>();
        //         auto id = entity->GetComponent<IDComponent>();

        //         if (transform && id) {
        //             Renderer2D::DrawSprite(
        //                 transform.Get().GetTransform(), // Transform
        //                 sprite.Get(),                   // SpriteRendererComponent
        //                 (int)id.Get().ID                // Entity ID
        //             );
        //         }
        //     });



        //     Exodia::Renderer2D::EndScene();
        // }
    }

    void RTypeLayer::OnImGUIRender()
    {
        EXODIA_PROFILE_FUNCTION();

        // ImGui::Begin("Settings");

        // ImGui::ColorEdit4("Square Color", glm::value_ptr(_SquareColor));

        // ImGui::End();
    }

    void RTypeLayer::OnEvent(Exodia::Event &event)
    {
        _CameraController.OnEvent(event);
        if (Exodia::Input::IsKeyPressed(Exodia::Key::SPACE)) {
            std::cout << "Space key is pressed" << std::endl;
            network.SendEvent(0x00);
        }
    }

    bool RTypeLayer::OnKeyPressedEvent(KeyPressedEvent &event) {

        int key = event.GetKeyCode();

        EXODIA_INFO("pressed {0}", key);
        _World[_currentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](UNUSED Entity *entity, ComponentHandle<ScriptComponent> script, auto tag) {
            if (tag.Get().Tag.rfind("Player", 0) != std::string::npos && script.Get().Instance != nullptr) {
                script.Get().Instance->OnKeyPressed(key);
            }
        });
        return true;

    };

    bool RTypeLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {

        int key = event.GetKeyCode();

        EXODIA_INFO("released {0}", key);
        _World[_currentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](UNUSED Entity *entity, ComponentHandle<ScriptComponent> script, auto tag) {

            if (tag.Get().Tag.rfind("Player", 0) != std::string::npos && script.Get().Instance != nullptr) {
                script.Get().Instance->OnKeyReleased(key);
            }
        });
        return false;
    };
};
