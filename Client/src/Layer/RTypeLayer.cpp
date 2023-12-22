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

    RTypeLayer::RTypeLayer() : Layer("R-Type"), _CameraController(1600.0f / 900.0f)
    {
        std::cout << "RTypeLayer constructor" << std::endl;
    };

    /////////////
    // Methods //
    /////////////

    void RTypeLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        auto commandLine = Application::Get().GetSpecification().CommandLineArgs;
        int port = 8083; // Default port
        if (commandLine.Count > 1) {
            port = std::stoi(commandLine[1]);
            if (port < 1024 || port > 65535) {
                Application::Get().Close();
                return;
            }
        }

        FramebufferSpecification fbSpec;

        fbSpec.Width  = Application::Get().GetWindow().GetWidth();
        fbSpec.Height = Application::Get().GetWindow().GetHeight();
        fbSpec.Attachments = {
            FramebufferTextureFormat::RGBA8,
            FramebufferTextureFormat::RED_INTEGER,
            FramebufferTextureFormat::Depth
        };

        _Framebuffer = Framebuffer::Create(fbSpec);

        this->network = std::make_unique<Exodia::Network::Network>(_worldNetwork, ioContextManager, port);
        network->Loop();
        network->SendAskConnect("127.0.0.1", 8082);

        // Create world
        _currentScene = GAME;
        _World[GAME] = CreateRef<Scene>();
        network->SetWorld(_World[_currentScene]->GetWorldPtr());
        _World[MENU] = CreateRef<Scene>();
        _World[GAME]->OnViewportResize(1600, 900);
        _World[MENU]->OnViewportResize(1600, 900);

        CollisionSystem *collisionSystem = new CollisionSystem();

        _World[GAME]->RegisterSystem(new AnimationSystem());
        _World[GAME]->RegisterSystem(new ScriptSystem());
        _World[GAME]->RegisterSystem(new MovingSystem(1.5f));
        _World[MENU]->RegisterSystem(new AnimationSystem());
        _World[MENU]->RegisterSystem(new ScriptSystem());
        _World[MENU]->RegisterSystem(new MovingSystem(1.5f));
        _World[GAME]->RegisterSystem(collisionSystem);

        //RType::EntityEventSubscriber *subscribe = new RType::EntityEventSubscriber(network);

        //_World[GAME]->Subscribe<Events::OnEntityCreated>(subscribe);
        //_World[GAME]->Subscribe<Events::OnEntityDestroyed>(subscribe);
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
        // CreatePataPata(_World);

        // Create background
        CreateBackground(_World);

        Entity *cameraMenu = _World[MENU]->CreateEntity("Camera");
        auto &camera_ = cameraMenu->AddComponent<CameraComponent>().Get();
        cameraMenu->GetComponent<TransformComponent>().Get().Translation = { 0.0f, 0.0f, 15.0f };
        camera_.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera_.Camera.SetViewportSize(1600, 900);
        cameraMenu->AddComponent<RigidBody2DComponent>().Get().Type = RigidBody2DComponent::BodyType::Static;

        // Create stars
        // CreateStars(_World);

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
            auto &sc = script.Get();
            auto &tc = tag.Get();

            //TODO: Check if player{client_id}
            if (tc.Tag.rfind("Player", 0) != std::string::npos && sc.Instance != nullptr) {
                sc.Instance->OnKeyPressed(key);

                network->SendEvent(key, true);
            }
        });
        return true;
    };

    bool RTypeLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {

        int key = event.GetKeyCode();

        EXODIA_INFO("released {0}", key);

        _World[_currentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](Entity *entity, auto script, auto tag) {
            (void)entity;
            auto &sc = script.Get();
            auto &tc = tag.Get();

            // TODO: Check if player{client_id}
            if (tc.Tag.rfind("Player", 0) != std::string::npos && sc.Instance != nullptr) {
                sc.Instance->OnKeyReleased(key);

                network->SendEvent(key, false);
            }
        });
        return false;
    };
};
