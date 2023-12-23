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

    RTypeLayer::RTypeLayer() : Layer("R-Type"), _WorldNetwork(nullptr), _Network(nullptr), _EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f)
    {
        CurrentScene = MENU;
    }

    /////////////
    // Methods //
    /////////////

    void RTypeLayer::OnAttach()
    {
        EXODIA_PROFILE_FUNCTION();

        Scenes[MENU] = CreateRef<Scene>();
        Scenes[MENU]->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

        // Create world
        /*
        Scenes[MENU]->RegisterSystem(new AnimationSystem());
        Scenes[MENU]->RegisterSystem(new ScriptSystem());
        Scenes[MENU]->RegisterSystem(new MovingSystem(1.5f));

        //RType::EntityEventSubscriber *subscribe = new RType::EntityEventSubscriber(_Network);
        CollisionSystem *collisionSystem = new CollisionSystem();

        Scenes[GAME] = CreateRef<Scene>();
        Scenes[GAME]->RegisterSystem(new AnimationSystem());
        Scenes[GAME]->RegisterSystem(new ScriptSystem());
        Scenes[GAME]->RegisterSystem(new MovingSystem(1.5f));
        Scenes[GAME]->RegisterSystem(collisionSystem);
        //Scenes[GAME]->Subscribe<Events::OnEntityCreated>(subscribe);
        //Scenes[GAME]->Subscribe<Events::OnEntityDestroyed>(subscribe);
        Scenes[GAME]->Subscribe<Events::OnCollisionEntered>(collisionSystem);
        Scenes[GAME]->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

        _Network->SetWorld(Scenes[CurrentScene]->GetWorldPtr());

        //TODO: Temp code

        // Create the camera entity
        Entity *cameraEntity = Scenes[GAME]->CreateEntity("Camera");

        auto &camera = cameraEntity->AddComponent<CameraComponent>().Get();
        cameraEntity->GetComponent<TransformComponent>().Get().Translation = { 0.0f, 0.0f, 15.0f };
        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
*/
        /* Removing rigid body for static camera
        auto body_camera = cameraEntity->AddComponent<RigidBody2DComponent>();
        body_camera.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_camera.Get().Mass = 0.0f;
        body_camera.Get().GravityScale = 0.0f;
        body_camera.Get().Velocity = glm::vec2{ 1.5f, 0.0f };
        */

        // Create the entities
        //CreatePlayer(Scenes, 0);

        // Create pata-pata
        // CreatePataPata(Scenes);

        // Create background
        /*CreateBackground(Scenes);

        Entity *cameraMenu = Scenes[MENU]->CreateEntity("Camera");

        auto &camera_ = cameraMenu->AddComponent<CameraComponent>().Get();
        cameraMenu->GetComponent<TransformComponent>().Get().Translation = { 0.0f, 0.0f, 15.0f };
        camera_.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera_.Camera.SetViewportSize(1600, 900);
        cameraMenu->AddComponent<RigidBody2DComponent>().Get().Type = RigidBody2DComponent::BodyType::Static;*/

        // Create stars
        // CreateStars(Scenes);

        // Create the camera
        //Scenes[CurrentScene]->OnRuntimeStart();
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

        // Scene Update
        {
            if (CurrentScene == GAME)
                Scenes[CurrentScene]->OnUpdateRuntime(ts);
            else {
                _EditorCamera.OnUpdate(ts);

                Scenes[CurrentScene]->OnUpdateEditor(ts, _EditorCamera);
            }
        }
    }

    void RTypeLayer::OnImGUIRender()
    {
        EXODIA_PROFILE_FUNCTION();
    }

    void RTypeLayer::OnEvent(Exodia::Event &event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyReleasedEvent));
    }

    bool RTypeLayer::OnKeyPressedEvent(KeyPressedEvent &event) {
        int key = event.GetKeyCode();

        if (CurrentScene == MENU) {
            if (key == Exodia::Key::ENTER) {
                auto commandLine = Application::Get().GetSpecification().CommandLineArgs;

                // TODO: Temp port ./r-type_client -p {port}
                int port = 8083; // Default port

                if (commandLine.Count > 1) {
                    port = std::stoi(commandLine[1]);

                    if (port < 1024 || port > 65535) {
                        Application::Get().Close();
                        return true;
                    }
                }

                CurrentScene = GAME;

                _WorldNetwork = World::CreateWorld();
                _Network = CreateScope<Network::Network>(_WorldNetwork, _IOContextManager, port);

                _Network->Loop();
                _Network->SendAskConnect("127.0.0.1", 8082);

                Scenes[GAME] = CreateRef<Scene>();
                Scenes[GAME]->SetWorld(_WorldNetwork);
                Scenes[CurrentScene]->OnRuntimeStart();
            }
        } else {
            Scenes[CurrentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](Entity *entity, auto script, auto tag) {
                auto &sc = script.Get();
                auto &tc = tag.Get();

                if (tc.Tag.rfind("Player", std::stoi(this->_Network->id)) != std::string::npos && sc.Instance != nullptr) {
                    sc.Instance->OnKeyPressed(key);

                    _Network->SendEvent(key, true);
                }

                (void)entity;
            });
        }

        return true;
    };

    bool RTypeLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {
        if (CurrentScene == MENU)
            return true;

        int key = event.GetKeyCode();

        Scenes[CurrentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>([&](Entity *entity, auto script, auto tag) {
            auto &sc = script.Get();
            auto &tc = tag.Get();

            // TODO: Check if player{client_id}
            if (tc.Tag.rfind("Player", std::stoi(this->_Network->id)) != std::string::npos && sc.Instance != nullptr) {
                sc.Instance->OnKeyReleased(key);

                _Network->SendEvent(key, false);
            }

            (void)entity;
        });
        return true;
    };
};
