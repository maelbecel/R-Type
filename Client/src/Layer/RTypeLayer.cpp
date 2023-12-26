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

    RTypeLayer::RTypeLayer() : Layer("R-Type"), _WorldNetwork(Exodia::World::CreateWorld()), _Network(nullptr) {};

    /////////////
    // Methods //
    /////////////

    void RTypeLayer::OnAttach() {
        EXODIA_PROFILE_FUNCTION();

        auto commandLine = Application::Get().GetSpecification().CommandLineArgs;

        // TODO: Temp port ./r-type_client -p {port}
        int port = 8083; // Default port
        if (commandLine.Count > 1) {
            port = std::stoi(commandLine[1]);

            if (port < 1024 || port > 65535) {
                Application::Get().Close();
                return;
            }
        }

        _Network = CreateScope<Network::Network>(_WorldNetwork, _IOContextManager, port);

        _Network->Loop();
        _Network->SendAskConnect("127.0.0.1",
                                 8082); // TODO: change ip and port when the server is on a different machine
        // Create world
        CurrentScene = GAME;

        Scenes[MENU] = CreateRef<Scene>();
        Scenes[MENU]->RegisterSystem(new AnimationSystem());
        Scenes[MENU]->RegisterSystem(new MovingSystem(1.5f));
        Scenes[MENU]->OnViewportResize(Application::Get().GetWindow().GetWidth(),
                                       Application::Get().GetWindow().GetHeight());

        // RType::EntityEventSubscriber *subscribe = new RType::EntityEventSubscriber(_Network);
        CollisionSystem *collisionSystem = new CollisionSystem();

        Scenes[GAME] = CreateRef<Scene>();
        Scenes[GAME]->RegisterSystem(new AnimationSystem());
        Scenes[GAME]->RegisterSystem(new MovingSystem(1.5f));
        Scenes[GAME]->RegisterSystem(collisionSystem);
        // Scenes[GAME]->Subscribe<Events::OnEntityCreated>(subscribe);
        // Scenes[GAME]->Subscribe<Events::OnEntityDestroyed>(subscribe);
        Scenes[GAME]->Subscribe<Events::OnCollisionEntered>(collisionSystem);
        Scenes[GAME]->OnViewportResize(Application::Get().GetWindow().GetWidth(),
                                       Application::Get().GetWindow().GetHeight());

        //Entity *music = Scenes[GAME]->CreateEntity("Background");

        //music->AddComponent<MusicComponent>(124013371145915, 0.5f, true);

        //Entity *text = Scenes[GAME]->CreateEntity("Text");

        //auto txt = text->AddComponent<TextRendererComponent>("\"From   the dark regions of space they\n came...Waging war upon us.\n One saviour stood his ground while all\n others were crushed under the alien\n assaul t...\n\n The Prototype Markl .\"");

        //txt.Get().Font = UUID(4521854574125);
        //txt.Get().Font = UUID(45121874124124);

        //auto transform = text->GetComponent<TransformComponent>();

        //transform.Get().Translation = {-10.0f, 3.0f, 0.0f};
        //transform.Get().Scale = {0.50f, 0.50f, 1.0f};

        _Network->SetWorld(Scenes[CurrentScene]->GetWorldPtr());

        // TODO: Temp code

        // Create the camera entity
        Entity *cameraEntity = Scenes[GAME]->CreateEntity("Camera");

        auto &camera = cameraEntity->AddComponent<CameraComponent>().Get();
        cameraEntity->GetComponent<TransformComponent>().Get().Translation = {0.0f, 0.0f, 15.0f};
        camera.Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
        camera.Camera.SetViewportSize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());

        /* Removing rigid body for static camera
        auto body_camera = cameraEntity->AddComponent<RigidBody2DComponent>();
        body_camera.Get().Type = RigidBody2DComponent::BodyType::Dynamic;
        body_camera.Get().Mass = 0.0f;
        body_camera.Get().GravityScale = 0.0f;
        body_camera.Get().Velocity = glm::vec2{ 1.5f, 0.0f };
        */

        // Create the entities
        // CreatePlayer(Scenes, 0);

        // Create pata-pata
        // CreatePataPata(Scenes);

        // Create stars
        // CreateStars(Scenes);

        // Create the camera
        Scenes[CurrentScene]->OnRuntimeStart();
    }

    void RTypeLayer::OnDetach() { EXODIA_PROFILE_FUNCTION(); }

    void RTypeLayer::OnUpdate(Exodia::Timestep ts) {
        EXODIA_PROFILE_FUNCTION();
        // Renderer Prep
        {
            EXODIA_PROFILE_SCOPE("Renderer Prep");

            Exodia::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            Exodia::RenderCommand::Clear();
        }

        // Update
        if (CurrentScene == GAME) {
        };

        // Update the world
        Scenes[CurrentScene]->OnUpdateRuntime(ts);
    }

    void RTypeLayer::OnImGUIRender() { EXODIA_PROFILE_FUNCTION(); }

    void RTypeLayer::OnEvent(Exodia::Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(RTypeLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(RTypeLayer::OnWindowResizeEvent));
    }

    bool RTypeLayer::OnKeyPressedEvent(KeyPressedEvent &event) {

        int key = event.GetKeyCode();

        Scenes[CurrentScene]->GetWorld().LockMutex();
        Scenes[CurrentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>(
            [&](Entity *entity, auto script, auto tag) {
                auto &sc = script.Get();
                auto &tc = tag.Get();

                if ((tc.Tag.compare("Player_" + _Network->id) == 0) && sc.Instance != nullptr) {
                    sc.Instance->OnKeyPressed(key);

                    _Network->SendEvent(key, true);
                }

                (void)entity;
            });
        Scenes[CurrentScene]->GetWorld().UnlockMutex();

        return true;
    };

    bool RTypeLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {

        int key = event.GetKeyCode();

        Scenes[CurrentScene]->GetWorld().LockMutex();
        Scenes[CurrentScene]->GetWorld().ForEach<ScriptComponent, TagComponent>(
            [&](Entity *entity, auto script, auto tag) {
                auto &sc = script.Get();
                auto &tc = tag.Get();

                if ((tc.Tag.compare("Player_" + _Network->id) == 0) && sc.Instance != nullptr) {
                    sc.Instance->OnKeyReleased(key);

                    _Network->SendEvent(key, false);
                }

                (void)entity;
            });
        Scenes[CurrentScene]->GetWorld().UnlockMutex();

        return false;
    };

    bool RTypeLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
        if (Scenes[CurrentScene] != nullptr)
            Scenes[CurrentScene]->OnViewportResize(event.GetWidth(), event.GetHeight());

        return true;
    }
}; // namespace Exodia
